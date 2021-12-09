#include <iostream>
#include <unordered_map>

#include "../Types/Types.h"
#include "ServerInterface.h"
#include "../Connection/Connection.h"

namespace network {
    class GameServer : public network::ServerInterface<GameMsg> {
    public:
        GameServer(uint16_t nPort) : network::ServerInterface<GameMsg>(nPort) {
        }

        std::unordered_map<uint32_t, sPlayerDescription> m_mapPlayerRoster;
        std::vector<uint32_t> m_vGarbageIDs;

    protected:
        bool OnClientConnect(std::shared_ptr<network::Connection<GameMsg>> client) override {
            return true;
        }

        void OnClientValidated(std::shared_ptr<network::Connection<GameMsg>> client) override {
            network::message<GameMsg> msg;
            msg.header.id = GameMsg::Client_Accepted;
            client->Send(msg);
        }

        void OnClientDisconnect(std::shared_ptr<network::Connection<GameMsg>> client) override {
            if (client) {
                if (m_mapPlayerRoster.find(client->GetID()) == m_mapPlayerRoster.end()) {
                }
                else {
                    auto& pd = m_mapPlayerRoster[client->GetID()];
                    std::cout << "Deleted player:" + std::to_string(pd.nUniqueID) + "\n";
                    m_mapPlayerRoster.erase(client->GetID());
                    m_vGarbageIDs.push_back(client->GetID());
                }
            }

        }

        void OnMessage(std::shared_ptr<network::Connection<GameMsg>> client, network::message<GameMsg>& msg) override {
            if (!m_vGarbageIDs.empty()) {
                for (auto pid : m_vGarbageIDs) {
                    network::message<GameMsg> m;
                    m.header.id = GameMsg::Game_RemovePlayer;
                    m << pid;
                    std::cout << "Deleting player: " << pid << "\n";
                    MessageAllClients(m);
                }
                m_vGarbageIDs.clear();
            }



            switch (msg.header.id) {
            case GameMsg::Client_RegisterWithServer: {
                sPlayerDescription desc;
                msg >> desc;
                desc.nUniqueID = client->GetID();
                m_mapPlayerRoster.insert_or_assign(desc.nUniqueID, desc);

                network::message<GameMsg> msgSendID;
                msgSendID.header.id = GameMsg::Client_AssignID;
                msgSendID << desc.nUniqueID;
                MessageClient(client, msgSendID);

                network::message<GameMsg> msgAddPlayer;
                msgAddPlayer.header.id = GameMsg::Game_AddPlayer;
                msgAddPlayer << desc;
                MessageAllClients(msgAddPlayer);

                for (const auto& player : m_mapPlayerRoster) {
                    network::message<GameMsg> msgAddOtherPlayers;
                    msgAddOtherPlayers.header.id = GameMsg::Game_AddPlayer;
                    msgAddOtherPlayers << player.second;
                    MessageClient(client, msgAddOtherPlayers);
                }
                break;
            }

            case GameMsg::Client_UnregisterWithServer: {
                break;
            }

            case GameMsg::Game_UpdatePlayer: {
                MessageAllClients(msg, client);
                break;
            }
            }

        }
    };

} // namespace network
