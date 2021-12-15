#pragma once

#include "player.h"
#include "map.h"
#include "SFML/Graphics.hpp"
#include "mapparser.h"
#include "SFML/Graphics.hpp"
#include "iostream"
#include <unistd.h>

namespace GameController {
    class GameController {
    public:
        explicit GameController();
        ~GameController();
        void Run(sf::RenderWindow& window);

    private:
        Player::Player* player;
        Map::Map map;
        std::vector<GameObject::GameObject*> gameObjects;

        std::array<bool, Player::KEYS_COUNT> keyState{};

        int gameStatus;

        void initPlayer();
        void handleKeys(sf::Event& event);
        void checkCollisionWithPlatforms(sf::Vector2f delta);
        void checkCollisionWithObjects(sf::Vector2f delta);
        void checkCollisionBetweenObjects();
        void gameOver(int status);
    };
}