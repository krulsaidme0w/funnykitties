namespace network {
            Server::Server(uint16_t nPort) : network::ServerInterface(nPort) {
            }

            bool Server::OnClientConnect(std::shared_ptr<network::connection<GameMsg>> client) override {
                return true;
            }

            void Server::OnClientValidated(std::shared_ptr<network::connection<GameMsg>> client) override {

            }

            void Server::OnClientDisconnect(std::shared_ptr<network::connection<GameMsg>> client) override {

            }

            void Server::OnMessage(std::shared_ptr<network::connection<GameMsg>> client, network::types::message<GameMsg>& msg) override {
            }

} // namespace network
