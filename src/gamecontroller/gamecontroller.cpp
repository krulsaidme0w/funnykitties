#include "gamecontroller.h"

#include "mapparser.h"

#include "SFML/Graphics.hpp"
#include "iostream"

GameController::GameController::GameController(): mWindow(sf::RenderWindow(sf::VideoMode(1920, 800), "PLAYER_TEST")) {

    mWindow.setFramerateLimit(120);
    initPlayer();

    Map::MapParser parser = Map::MapParser();
    this->map = parser.GetMap("../../levels/level_1/map.json");

    this->keyState = std::array<bool, Player::KEYS_COUNT>{false, false, false};
}

GameController::GameController::~GameController() {
    delete player;
}

void GameController::GameController::Run() {

    while(mWindow.isOpen()) {

        processEvents();


        update();

        render();
    }
}

void GameController::GameController::initPlayer() {
    sf::Vector2f speed;
    speed.x = 1.5;
    speed.y = 0;
    float jumpAcceleration = -8;
    float gravitation = 0.09;
    bool enableGravitation = 1;
    float maxSpeed = 100;
    std::string path = "../assets/player/cat.png";

    this->player = new Player::Player(speed, jumpAcceleration, gravitation, maxSpeed, path);
    this->player->SetCoordinates(sf::Vector2f(1920 / 2, 1080 / 2));
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
                this->map.MoveX(-1 * (tile.getPosition().x + tileSize.first - player->GetCoordinates().x));
            }

            if (delta.x == 1) {
                this->map.MoveX(player->GetCoordinates().x + playerSize.x - tile.getPosition().x);
            }
        }
    }
}

void GameController::GameController::processEvents() {
    sf::Event event{};
    while (mWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            mWindow.close();

        handleKeys(event);
    }

}

void GameController::GameController::update() {
    this->map.Update(keyState, this->player->GetSpeed().x);

    sf::Vector2f delta = this->player->Update(keyState);
    keyState[Player::KEY_JUMP] = false;
    checkCollisionWithPlatforms(delta);
}

void GameController::GameController::render() {
    mWindow.clear(sf::Color(56, 53, 53, 255));

    this->map.Draw(mWindow);
    mWindow.draw(this->player->GetSprite());

    mWindow.display();
}
