#include "gtest/gtest.h"

#include "player.h"
#include "gamecontroller.h"

#include "SFML/Graphics.hpp"
#include "iostream"

#include "fstream"

#include "map.h"
#include "mapparser.h"

TEST(PLAYER_TESTS, PLAYER_DRAW)
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "PLAYER_TEST");
    window.setFramerateLimit(60);

    sf::Vector2f speed;
    speed.x = 1;
    speed.y = 0;
    float jumpAcceleration = -5;
    float gravitation = 0.05;
    float maxSpeed = 100;

    int width = 25;
    int height = 18;

    Player::Player player = Player::Player(speed, jumpAcceleration, gravitation, maxSpeed, "../../../assets/player/cat.png");
    player.SetCoordinates(sf::Vector2f(300, 300));

    std::vector<std::vector<std::pair<sf::Sprite, sf::Texture>>> map{};

    auto* sprites = new sf::Sprite[height * width];
    auto* textures = new sf::Texture[height * width];

    for(int i = 0; i < height * width; ++i) {
        textures[i].loadFromFile("../../../assets/player/cat.png");
        sprites[i].setTexture(textures[i]);
        sprites[i].setPosition(float(i % width) * 32, float(i / width) * 32);
    }

    std::array<bool, Player::KEYS_COUNT> keyState;
    keyState[0] = false;
    keyState[1] = false;
    keyState[2] = false;

    while (window.isOpen()) {

        keyState[Player::KEY_JUMP] = false;


        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

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

        window.clear();

        for(int i = 0; i < height * width; ++i) {
            window.draw(sprites[i]);
        }

        player.Update(keyState);

        window.draw(player.GetSprite());

        window.display();
    }

    delete[] sprites;
    delete[] textures;
}

TEST(GC, GC) {
    sf::RenderWindow window(sf::VideoMode(1920, 960), "PLAYER_TEST");
    window.setFramerateLimit(60);

    GameController::GameController gamecontroller = GameController::GameController();
    gamecontroller.Run(window);
}


