#include <iostream>

namespace network {
    class ServerInterface {
        public:
			ServerInterface(uint16_t port) {
			}

			virtual ~ServerInterface() {
				Stop();
			}

			bool Start() {
                std::cout << "[SERVER] is running on port !\n";

			}

			void Stop() {
				std::cout << "[SERVER] Stopped!\n";
			}

			void WaitForClientConnection() {
			}

			void MessageClient(std::shared_ptr<connection<T>> client, const message<T>& msg) {
			}
			
			void MessageAllClients(const message<T>& msg, std::shared_ptr<connection<T>> pIgnoreClient = nullptr) {
			}

			void Update(size_t nMaxMessages = -1, bool bWait = false) {
			}

		protected:

			virtual bool OnClientConnect(std::shared_ptr<connection<T>> client) {
				return false;
			}

			virtual void OnClientDisconnect(std::shared_ptr<connection<T>> client) {

			}

			virtual void OnMessage(std::shared_ptr<connection<T>> client, message<T>& msg) {

			}

		public:
			virtual void OnClientValidated(std::shared_ptr<connection<T>> client) {

			}


		protected:
			tsqueue<owned_message<T>> m_qMessagesIn;

			std::deque<std::shared_ptr<connection<T>>> m_deqConnections;

			asio::io_context m_asioContext;
			std::thread m_threadContext;

			asio::ip::tcp::acceptor m_asioAcceptor;

			uint32_t nIDCounter;
		};

    };
    
}; // namespace network
