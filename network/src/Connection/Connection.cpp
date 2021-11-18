#include "Connection.h"

namespace network {

			Connection::Connection() {

            }

			virtual ~Connection::Connection() {

            }

		
			uint32_t Connection::GetID() const {

            }

			void Connection::ConnectToClient(network::serverInterface<T>* server, uint32_t uid = 0) {

            }

			void Connection::ConnectToServer(const asio::ip::tcp::resolver::results_type& endpoints) {

            }


			void Connection::Disconnect() {

            }

			bool Connection::IsConnected() const {

            }
			void Connection::StartListening() {

            }

			void Connection::Send(const message<T>& msg) {
                
            }

    }
    
} // namespace network
