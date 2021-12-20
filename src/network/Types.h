#pragma once

#include <cstdint>

#include "SFML/Graphics.hpp"

#include "Network.h"

enum class GameMsg : uint32_t {
    Server_GetStatus,
    Server_GetPing,

    Client_Accepted,
    Client_AssignID,
    Client_RegisterWithServer,
    Client_UnregisterWithServer,

    Game_AddPlayer,
    Game_RemovePlayer,
    Game_UpdatePlayer,
};

struct sPlayerDescription {
    uint32_t nUniqueID = 0;
    uint32_t nAvatarID = 0;

    int side;

    sf::Vector2f vPos;
    sf::Vector2f vVel;
};