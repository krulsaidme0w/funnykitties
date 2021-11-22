#include "gtest/gtest.h"

#include "player.h"

#include "SFML/Graphics.hpp"
#include "iostream"


TEST(PLAYER_TESTS, PLAYER_DRAW)
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "PLAYER_TEST");

    window.setFramerateLimit(60);

    sf::Vector2f speed;
    speed.x = 1;
    speed.y = 0;
    float jumpAcceleration = -2.5;
    float gravitation = 0.05;
    float maxSpeed = 100000;

    sf::Texture texture;
    if(!texture.loadFromFile("../../../assets/player/cat.png")) {
        std::cout << "bad path\n";
    }

    Player::Player player = Player::Player(speed, jumpAcceleration, gravitation, maxSpeed, texture);
    player.SetCoordinates(sf::Vector2f(300, 300));

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

        player.Update(keyState);

        window.draw(player.GetSprite());

        std::cout << player.GetCoordinates().x << ' ' << player.GetCoordinates().y << '\n';

        window.display();

    }
}
