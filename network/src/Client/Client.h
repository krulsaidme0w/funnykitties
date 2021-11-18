#include <iostream>
#include "Tsqueue/Tsqueue.h"
#include "Types/Types.h"

namespace network {
    class Client {
        public:
			Client() 
			{}

			virtual ~Client()
			{
				Disconnect();
			}

		public:
			bool Connect(const std::string& host, const uint16_t port) {

            }

			void Disconnect() {
            }

			bool IsConnected() {

            }

		public:
			void Send(const network::types::message<T>& msg) {

            }

			Tsqueue<network::types::owned_message<T>>& Incoming() {

            }

		protected:
			asio::io_context m_context;
			std::thread thrContext;
			std::unique_ptr<connection<T>> m_connection;
			
		private:
			Tsqueue<network::types::owned_message<T>> m_qMessagesIn;
    };
    
}; // namespace network
