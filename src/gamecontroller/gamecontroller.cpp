#include "gamecontroller.h"

#include "mapparser.h"

#include "SFML/Graphics.hpp"
#include "iostream"

GameController::GameController::GameController() {
    initPlayer();

    Map::MapParser parser = Map::MapParser();
    map = parser.GetMap("../../levels/level_1/map.json");

    keyState = std::array<bool, Player::KEYS_COUNT>{false, false, false};
}

GameController::GameController::~GameController() {

}

void GameController::GameController::Run(sf::RenderWindow& window) {

    while(window.isOpen()) {

        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            handleKeys(event);
        }

        window.clear();

        map.Update(keyState, player->GetSpeed().x);

        sf::Vector2f delta = player->Update(keyState);
        keyState[Player::KEY_JUMP] = false;
        checkCollisionWithPlatforms(delta);
        map.Draw(window);
        window.draw(player->GetSprite());

        window.display();
    }
}

void GameController::GameController::initPlayer() {
    sf::Vector2f speed;
    speed.x = 1.5;
    speed.y = 0;
    const float jumpAcceleration = -8;
    const float gravitation = 0.09;
    const bool enableGravitation = 1;
    const float maxSpeed = 100;
    const std::string path = "../assets/player/cat.png";

    player = std::make_unique<Player::Player>(speed, jumpAcceleration, gravitation, maxSpeed, path);
    player->SetCoordinates(sf::Vector2f(1920 / 2, 1080 / 2));
}

void GameController::GameController::handleKeys(sf::Event& event) {

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        keyState[Player::KEY_LEFT] = true;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        keyState[Player::KEY_RIGHT] = true;
    }

    if (event.type == sf::Event::KeyReleased) {
        switch(event.key.code){
            case sf::Keyboard::A:{
                keyState[Player::KEY_LEFT] = false;
                break;
            }
            case sf::Keyboard::D:{
                keyState[Player::KEY_RIGHT] = false;
                break;
            }
            case sf::Keyboard::Space: {
                keyState[Player::KEY_JUMP] = true;
                break;
            }

            default:
                break;
        }
    }
}

void GameController::GameController::checkCollisionWithPlatforms(sf::Vector2f delta) {

    sf::Vector2u playerSize = player->GetSprite().getTexture()->getSize();
    std::pair<int, int> tileSize = map.GetTileSize();
    std::vector<sf::Sprite> tiles = map.GetTilesFromLayer("platform");

    for(auto& tile : tiles) {
        if(player->GetSprite().getGlobalBounds().intersects(tile.getGlobalBounds())) {

            sf::Vector2f speed = player->GetSpeed();

            if(speed.y < 0) {
                player->SetCoordinates(sf::Vector2f(player->GetCoordinates().x, tile.getPosition().y + tileSize.second));
            }

            if(speed.y > 0 && player->GetCoordinates().y + playerSize.y < tile.getPosition().y + playerSize.y) {
                player->SetCoordinates(sf::Vector2f(player->GetCoordinates().x, tile.getPosition().y - playerSize.y));
                player->SetState(Player::ON_GROUND);
                player->SetSpeed(sf::Vector2f(speed.x, 0));
            }
        }

        if(player->GetSprite().getGlobalBounds().intersects(tile.getGlobalBounds())) {
            if (delta.x == -1) {
                map.MoveX(-1 * (tile.getPosition().x + tileSize.first - player->GetCoordinates().x));
            }

            if (delta.x == 1) {
                map.MoveX(player->GetCoordinates().x + playerSize.x - tile.getPosition().x);
            }
        }
    }
}
