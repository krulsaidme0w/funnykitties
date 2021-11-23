#include "gamecontroller.h"

#include "SFML/Graphics.hpp"

GameController::GameController::GameController() {
    initPlayer();
    this->map.LoadFromFile("../../../levels/demo_map.tmx");
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

        window.clear();

        map.Draw(window);

        this->player->Update(keyState);
        keyState[Player::KEY_JUMP] = false;
        window.draw(this->player->GetSprite());

        window.display();
    }
}

void GameController::GameController::initPlayer() {
    sf::Vector2f speed;
    speed.x = 1;
    speed.y = 0;
    float jumpAcceleration = -2.5;
    float gravitation = 0.05;
    float maxSpeed = 100;
    std::string path = "../../../assets/player/cat.png";

    this->player = new Player::Player(speed, jumpAcceleration, gravitation, maxSpeed, path);
    this->player->SetCoordinates(sf::Vector2f(300, 300));
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
