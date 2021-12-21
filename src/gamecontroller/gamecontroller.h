#pragma once

#include "player.h"
#include "map.h"
#include "SFML/Graphics.hpp"
#include "mapparser.h"
#include "SFML/Graphics.hpp"
#include "iostream"
#include <unistd.h>
#include "../network/Types.h"

namespace GameController {
    class GameController : public network::client_interface<GameMsg> {
    public:
        explicit GameController(std::string levelMap);
        ~GameController();
        void Run(sf::RenderWindow& window);

    private:
        Player::Player* player;
        Map::Map map;
        std::vector<GameObject::GameObject*> gameObjects;
        std::array<bool, Player::KEYS_COUNT> keyState{};
        std::string path = "../../assets/player/jump.png";
        sf::Texture img;
        AnimationController::AnimationController animationController;


        /*
         * Network
         */

        std::unordered_map<uint32_t, sPlayerDescription> mapObjects;
        bool bWaitingForConnection = true;
        uint32_t nPlayerID = 0;
        sPlayerDescription descPlayer;


        int gameStatus;

        void initPlayer();
        void handleKeys(sf::Event& event);
        void checkCollisionWithPlatforms(sf::Vector2f delta);
        void checkCollisionWithObjects(sf::Vector2f delta);
        void checkCollisionBetweenObjects();
        void gameOver(int status);
    };
}