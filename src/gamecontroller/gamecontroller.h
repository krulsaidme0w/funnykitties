#pragma once

#include "player.h"
#include "map.h"

#include "SFML/Graphics.hpp"
#include "memory"

namespace GameController {
    class GameController {
    public:
        explicit GameController();
        ~GameController();
        void Run(sf::RenderWindow& window);
    private:
        std::unique_ptr<Player::Player> player;
        Map::Map map;
        std::array<bool, Player::KEYS_COUNT> keyState{};

        void initPlayer();
        void handleKeys(sf::Event& event);
        void checkCollisionWithPlatforms(sf::Vector2f delta);
    };
}