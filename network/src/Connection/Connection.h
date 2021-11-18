
#include "Connection.h"

namespace network {
    class Connection {
		public:
        enum class owner
        {
            server,
            client
        };

		public:
			Connection();

			virtual ~Connection();
		
			uint32_t GetID() const;

		public:
			void ConnectToClient(network::severInterface<T>* server, uint32_t uid = 0);

			void ConnectToServer(const asio::ip::tcp::resolver::results_type& endpoints);

			void Disconnect();

			bool IsConnected() const;
			void StartListening();

		public:
			void Send(const message<T>& msg);


		protected:
			asio::ip::tcp::socket m_socket;

			asio::io_context& m_asioContext;

			tsqueue<message<T>> m_qMessagesOut;

			tsqueue<owned_message<T>>& m_qMessagesIn;

			message<T> m_msgTemporaryIn;

			owner m_nOwnerType = owner::server;

			uint64_t m_nHandshakeOut = 0;
			uint64_t m_nHandshakeIn = 0;
			uint64_t m_nHandshakeCheck = 0;


			bool m_bValidHandshake = false;
			bool m_bConnectionEstablished = false;

			uint32_t id = 0;

    }
    
} // namespace network
