#include <iostream>
#include "../Tsqueue/Tsqueue.h"
#include "../Types/Types.h"

#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>


namespace network {
    template <typename T>
		class ClientInterface {
		public:
			ClientInterface() {}

			virtual ~ClientInterface() {
				Disconnect();
			}

		public:
			bool Connect(const std::string& host, const uint16_t port) {
				try {
					boost::asio::ip::tcp::resolver resolver(m_context);
					boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, std::to_string(port));

					m_connection = std::make_unique<Connection<T>>(Connection<T>::owner::client, m_context, boost::asio::ip::tcp::socket(m_context), m_qMessagesIn);
					
					m_connection->ConnectToServer(endpoints);

					thrContext = std::thread([this]() { m_context.run(); });
				}
				catch (std::exception& e) {
					std::cerr << "Client Exception: " << e.what() << "\n";
					return false;
				}
				return true;
			}

			void Disconnect() {
				if(IsConnected()) {
					m_connection->Disconnect();
				}

				m_context.stop();
				if (thrContext.joinable())
					thrContext.join();

				m_connection.release();
			}

			bool IsConnected() {
				if (m_connection)
					return m_connection->IsConnected();
				else
					return false;
			}

		public:
			void Send(const message<T>& msg) {
				if (IsConnected())
					 m_connection->Send(msg);
			}

			Tsqueue<owned_message<T>>& Incoming() {
				return m_qMessagesIn;
			}

		protected:
			boost::asio::io_context m_context;
			std::thread thrContext;
			std::unique_ptr<Connection<T>> m_connection;
			
		private:
			Tsqueue<owned_message<T>> m_qMessagesIn;
		};
    
}; // namespace network
