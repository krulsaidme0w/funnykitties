#include "ServerInterface.h"

namespace network {
    class Server : public ServerInterface {
        public:
            Server(uint16_t nPort) : network::ServerInterface(nPort) {
            }

        protected:
            bool OnClientConnect(std::shared_ptr<network::connection<GameMsg>> client) override {
                return true;
            }

            void OnClientValidated(std::shared_ptr<network::connection<GameMsg>> client) override {

            }

            void OnClientDisconnect(std::shared_ptr<network::connection<GameMsg>> client) override {

            }

            void OnMessage(std::shared_ptr<network::connection<GameMsg>> client, network::types::message<GameMsg>& msg) override {
            }

    }
    
} // namespace network
