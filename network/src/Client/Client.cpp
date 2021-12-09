#include <iostream>
#include "ClientInterface.h"
#include "../Tsqueue/Tsqueue.h"
#include "../Types/Types.h"
#include <unordered_map>

namespace network {

    class GameController : network::ClientInterface<GameMsg> {
    public:
        GameController() {
        }

    private:
        void handleKeys();
        void update();
        void render();

    private:
        std::unordered_map<uint32_t, sPlayerDescription> mapObjects;
        uint32_t nPlayerID = 0;
        sPlayerDescription descPlayer;

        bool bWaitingForConnection = true;

    public:
        bool OnUserCreate() {
            if (Connect("127.0.0.1", 8080)) {
                return true;
            }
            return false;
        }

        bool OnUserUpdate(float fElapsedTime) {
            if (IsConnected()) {
                while (!Incoming().empty()) {
                    auto msg = Incoming().pop_front().msg;

                    switch (msg.header.id) {
                    case(GameMsg::Client_Accepted): {
                        std::cout << "Server accepted client - you're in!\n";
                        message<GameMsg> msg;
                        msg.header.id = GameMsg::Client_RegisterWithServer;
                        descPlayer.vPos = { 3.0f, 3.0f };
                        msg << descPlayer;
                        Send(msg);
                        break;
                    }

                    case(GameMsg::Client_AssignID): {
                        msg >> nPlayerID;
                        std::cout << "Assigned Client ID = " << nPlayerID << "\n";
                        break;
                    }

                    case(GameMsg::Game_AddPlayer): {
                        sPlayerDescription desc;
                        msg >> desc;
                        mapObjects.insert_or_assign(desc.nUniqueID, desc);

                        if (desc.nUniqueID == nPlayerID) {
                            bWaitingForConnection = false;
                        }
                        break;
                    }

                    case(GameMsg::Game_RemovePlayer): {
                        uint32_t nRemovalID = 0;
                        msg >> nRemovalID;
                        mapObjects.erase(nRemovalID);
                        break;
                    }

                    case(GameMsg::Game_UpdatePlayer): {
                        sPlayerDescription desc;
                        msg >> desc;
                        mapObjects.insert_or_assign(desc.nUniqueID, desc);
                        break;
                    }


                    }
                }
            }

            if (bWaitingForConnection) {
                return true;
            }


    //        handleKeys();
    //        update();
    //        render();

            message<GameMsg> msg;
            msg.header.id = GameMsg::Game_UpdatePlayer;
            msg << mapObjects[nPlayerID];
            Send(msg);
            return true;
        }
    };
    
}; // namespace network
