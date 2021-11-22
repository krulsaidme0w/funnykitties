#pragma once

#include "gameobject.h"

#include "SFML/Graphics.hpp"
#include "iostream"

namespace Player {

    enum KEYS {
        KEY_LEFT,
        KEY_RIGHT,
        KEY_JUMP,
        KEYS_COUNT
    };

    class Player : public GameObject::GameObject {
    public:
        Player(sf::Vector2f speed, float jumpAcceleration, float gravitation, float maxSpeed, sf::Texture texture);
        ~Player() final;

        virtual void Update(std::array<bool, KEYS_COUNT> keyState);

        void SetSpeed(sf::Vector2f speed);
        void SetJumpAcceleration(float jumpAcceleration);
        void SetGravitation(float gravitation);

    private:

        enum SIDE {
            LEFT,
            RIGHT
        };

        sf::Vector2f speed;

        float jumpAcceleration;
        float gravitation;
        float maxSpeed;

        void handleKeys(std::array<bool, KEYS_COUNT> keyState);
        void moveX(SIDE);
        void moveY();
        void jump();
    };
}