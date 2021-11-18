#include <iostream>
#include "ClientInterface.h"
#include "Tsqueue/Tsqueue.h"
#include "Types/Types.h"

namespace network {
			bool Client::Connect(const std::string& host, const uint16_t port) {

            }

			void Client::Disconnect() {
            }

			bool Client::IsConnected() {

            }

			void Client::Send(const network::types::message<T>& msg) {

            }

			Tsqueue<network::types::owned_message<T>>& Client::Incoming() {

            }
    
}; // namespace network
