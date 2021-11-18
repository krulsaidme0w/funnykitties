#include "ServerInterface.h"

namespace network {
    class Server : public ServerInterface {
        public:
            Server(uint16_t nPort) : network::ServerInterface(nPort) {
            }

        protected:
            bool OnClientConnect(std::shared_ptr<network::types<GameMsg>> client) override {
                return true;
            }

            void OnClientValidated(std::shared_ptr<network::types<GameMsg>> client) override {

            }

            void OnClientDisconnect(std::shared_ptr<network::types<GameMsg>> client) override {

            }

            void OnMessage(std::shared_ptr<network::types<GameMsg>> client, olc::net::message<GameMsg>& msg) override {
            }

    }
    
} // namespace network
