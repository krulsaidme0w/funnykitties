#include "gamecontroller.h"

#include "mapparser.h"

#include "SFML/Graphics.hpp"
#include "iostream"

GameController::GameController::GameController() {
    initPlayer();

    Map::MapParser parser = Map::MapParser();
    this->map = parser.GetMap("../../../levels/map.json");

    this->keyState = std::array<bool, Player::KEYS_COUNT>{false, false, false};
}

GameController::GameController::~GameController() {
    delete player;
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

        window.clear(sf::Color(56, 53, 53, 255));

        this->map.Draw(window);

        this->player->Update(keyState);
        keyState[Player::KEY_JUMP] = false;
        checkCollisionWithPlatforms();
        window.draw(this->player->GetSprite());

        this->map.Update(keyState, this->player->GetSpeed().x);

        window.display();
    }
}

void GameController::GameController::initPlayer() {
    sf::Vector2f speed;
    speed.x = 1.5;
    speed.y = 0;
    float jumpAcceleration = -5;
    float gravitation = 0.09;
    float maxSpeed = 100;
    std::string path = "../../../assets/player/cat1.png";

    this->player = new Player::Player(speed, jumpAcceleration, gravitation, maxSpeed, path);
    this->player->SetCoordinates(sf::Vector2f(300, 100));
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

void GameController::GameController::checkCollisionWithPlatforms() {

    sf::Vector2f playerPosition = player->GetCoordinates();
    sf::Vector2u playerSize = player->GetSprite().getTexture()->getSize();

    std::pair<int, int> tileSize = map.GetTileSize();
//    std::pair<int, int> additionalTiles = std::make_pair(playerSize.x / tileSize.first + 1, playerSize.y / tileSize.second + 1);
//
//    std::pair<int, int> playerRowColumn = std::make_pair(playerPosition.x / tileSize.first, playerPosition.y / tileSize.second);
//
//    std::pair<int, int> mapSize = map.GetSize();

    std::vector<sf::Sprite> tiles = map.GetTilesFromLayer("platform");

    for(int index = 0; index < tiles.size(); ++index) {
        if(player->GetSprite().getGlobalBounds().intersects(tiles[index].getGlobalBounds())) {
//            if(player->GetSide() == Player::SIDE::LEFT) {
//                player->SetCoordinates(sf::Vector2f(tiles[index].getPosition().x + tileSize.first, player->GetCoordinates().y));
//            }
//            if(player->GetSide() == Player::SIDE::RIGHT) {
//                player->SetCoordinates(sf::Vector2f(tiles[index].getPosition().x - playerSize.x, player->GetCoordinates().y));
//            }

            sf::Vector2f speed = player->GetSpeed();

            if(speed.y < 0) {
                player->SetCoordinates(sf::Vector2f(player->GetCoordinates().x, tiles[index].getPosition().y + tileSize.second));
            }

            if(speed.y > 0) {
                player->SetCoordinates(sf::Vector2f(player->GetCoordinates().x, tiles[index].getPosition().y - playerSize.y));
                player->SetState(Player::ON_GROUND);
                player->SetSpeed(sf::Vector2f(speed.x, 0));
            }

        }
    }
}
