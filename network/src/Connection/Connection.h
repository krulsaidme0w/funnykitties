#include "../Types/Types.h"
#include "../Tsqueue/Tsqueue.h"
#include <memory>



#define ASIO_STANDALONE
#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>
#include "../Server/ServerInterface.h"


namespace network {
    template<typename T>
    class Connection : public std::enable_shared_from_this<Connection<T>> {
    public:
        enum class owner {
            server,
            client
        };

    public:
        Connection(owner parent, boost::asio::io_context& asioContext, boost::asio::ip::tcp::socket socket, network::Tsqueue<owned_message<T>>& qIn)
                : m_asioContext(asioContext), m_socket(std::move(socket)), m_qMessagesIn(qIn) {
            m_nOwnerType = parent;

            if (m_nOwnerType == owner::server) {
                m_nHandshakeOut = uint64_t(std::chrono::system_clock::now().time_since_epoch().count());

                m_nHandshakeCheck = Validate(m_nHandshakeOut);
            }
            else {
                m_nHandshakeIn = 0;
                m_nHandshakeOut = 0;
            }
        }

        virtual ~Connection() {}

        uint32_t GetID() const {
            return id;
        }

    public:
        void ConnectToClient(network::ServerInterface<T>* server, uint32_t uid = 0) {
            if (m_nOwnerType == owner::server) {
                if (m_socket.is_open()) {
                    id = uid;


                    WriteValidation();

                    ReadValidation(server);
                }
            }
        }

        void ConnectToServer(const boost::asio::ip::tcp::resolver::results_type& endpoints) {
            if (m_nOwnerType == owner::client) {
                boost::asio::async_connect(m_socket, endpoints,
                                           [this](std::error_code ec, boost::asio::ip::tcp::endpoint endpoint) {
                                               if (!ec) {

                                                   ReadValidation();
                                               }
                                           });
            }
        }


        void Disconnect() {
            if (IsConnected())
                boost::asio::post(m_asioContext, [this]() { m_socket.close(); });
        }

        bool IsConnected() const {
            return m_socket.is_open();
        }

        void StartListening() {

        }

    public:
        void Send(const message<T>& msg) {
            boost::asio::post(m_asioContext,
                              [this, msg]() {
                                  bool bWritingMessage = !m_qMessagesOut.empty();
                                  m_qMessagesOut.push_back(msg);
                                  if (!bWritingMessage) {
                                      WriteHeader();
                                  }
                              });
        }



    private:
        void WriteHeader() {
            boost::asio::async_write(m_socket, boost::asio::buffer(&m_qMessagesOut.front().header, sizeof(message_header<T>)),
                                     [this](std::error_code ec, std::size_t length) {
                                         if (!ec) {
                                             if (m_qMessagesOut.front().body.size() > 0) {
                                                 WriteBody();
                                             }
                                             else {
                                                 m_qMessagesOut.pop_front();

                                                 if (!m_qMessagesOut.empty()) {
                                                     WriteHeader();
                                                 }
                                             }
                                         }
                                         else {
                                             std::cout << "[" << id << "] Write Header Fail.\n";
                                             m_socket.close();
                                         }
                                     });
        }

        void WriteBody() {
            boost::asio::async_write(m_socket, boost::asio::buffer(m_qMessagesOut.front().body.data(), m_qMessagesOut.front().body.size()),
                                     [this](std::error_code ec, std::size_t length) {
                                         if (!ec) {
                                             m_qMessagesOut.pop_front();

                                             if (!m_qMessagesOut.empty()) {
                                                 WriteHeader();
                                             }
                                         }
                                         else {
                                             std::cout << "[" << id << "] Write Body Fail.\n";
                                             m_socket.close();
                                         }
                                     });
        }

        void ReadHeader() {
            boost::asio::async_read(m_socket, boost::asio::buffer(&m_msgTemporaryIn.header, sizeof(message_header<T>)),
                                    [this](std::error_code ec, std::size_t length) {
                                        if (!ec) {
                                            if (m_msgTemporaryIn.header.size > 0) {
                                                m_msgTemporaryIn.body.resize(m_msgTemporaryIn.header.size);
                                                ReadBody();
                                            }
                                            else {
                                                AddToIncomingMessageQueue();
                                            }
                                        }
                                        else {
                                            std::cout << "[" << id << "] Read Header Fail.\n";
                                            m_socket.close();
                                        }
                                    });
        }

        void ReadBody() {
            boost::asio::async_read(m_socket, boost::asio::buffer(m_msgTemporaryIn.body.data(), m_msgTemporaryIn.body.size()),
                                    [this](std::error_code ec, std::size_t length) {
                                        if (!ec) {
                                            AddToIncomingMessageQueue();
                                        }
                                        else {
                                            std::cout << "[" << id << "] Read Body Fail.\n";
                                            m_socket.close();
                                        }
                                    });
        }

        uint64_t Validate(uint64_t nInput) {
            return nInput;
        }

        void WriteValidation() {
            boost::asio::async_write(m_socket, boost::asio::buffer(&m_nHandshakeOut, sizeof(uint64_t)),
                                     [this](std::error_code ec, std::size_t length) {
                                         if (!ec) {
                                             if (m_nOwnerType == owner::client)
                                                 ReadHeader();
                                         }
                                         else {
                                             m_socket.close();
                                         }
                                     });
        }

        void ReadValidation(network::ServerInterface<T>* server = nullptr) {
            boost::asio::async_read(m_socket, boost::asio::buffer(&m_nHandshakeIn, sizeof(uint64_t)),
                                    [this, server](std::error_code ec, std::size_t length) {
                                        if (!ec) {
                                            if (m_nOwnerType == owner::server) {

                                                if (m_nHandshakeIn == m_nHandshakeCheck) {
                                                    std::cout << "Client Validated" << std::endl;
                                                    server->OnClientValidated(this->shared_from_this());

                                                    ReadHeader();
                                                }
                                                else {
                                                    std::cout << "Client Disconnected (Fail Validation)" << std::endl;
                                                    m_socket.close();
                                                }
                                            }
                                            else {
                                                m_nHandshakeOut = Validate(m_nHandshakeIn);

                                                WriteValidation();
                                            }
                                        }
                                        else {
                                            std::cout << "Client Disconnected (ReadValidation)" << std::endl;
                                            m_socket.close();
                                        }
                                    });
        }

        void AddToIncomingMessageQueue() {
            if(m_nOwnerType == owner::server)
                m_qMessagesIn.push_back({ this->shared_from_this(), m_msgTemporaryIn });
            else
                m_qMessagesIn.push_back({ nullptr, m_msgTemporaryIn });

            ReadHeader();
        }

    protected:
        boost::asio::ip::tcp::socket m_socket;

        boost::asio::io_context& m_asioContext;

        network::Tsqueue<message<T>> m_qMessagesOut;

        network::Tsqueue<owned_message<T>>& m_qMessagesIn;

        message<T> m_msgTemporaryIn;

        owner m_nOwnerType = owner::server;

        uint64_t m_nHandshakeOut = 0;
        uint64_t m_nHandshakeIn = 0;
        uint64_t m_nHandshakeCheck = 0;


        bool m_bValidHandshake = false;
        bool m_bConnectionEstablished = false;

        uint32_t id = 0;

    };

} // namespace network
