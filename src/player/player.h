#pragma once

#include "gameobject.h"
#include "animationcontroller.h"

#include "SFML/Graphics.hpp"
#include "iostream"

namespace Player {

    enum KEYS {
        KEY_LEFT,
        KEY_RIGHT,
        KEY_JUMP,
        KEYS_COUNT
    };

    enum SIDE {
        LEFT,
        RIGHT
    };

    enum STATE {
        JUMPING,
        FALLING,
        ON_GROUND
    };

    class Player final : public GameObject::GameObject {
    public:
        explicit Player(sf::Vector2f speed, float jumpAcceleration, float gravitation, float maxSpeed, std::string path);
        explicit Player();
        ~Player() final;

        virtual sf::Vector2f Update(std::array<bool, KEYS_COUNT> keyState);

        void SetSpeed(sf::Vector2f speed);
        void SetJumpAcceleration(float jumpAcceleration);
        void SetGravitation(float gravitation);
        void SetMaxSpeed(float maxSpeed);
        void SetState(STATE);

        sf::Vector2f GetSpeed() const;
        float GetJumpAcceleration() const;
        float GetGravitation() const;
        float GetMaxSpeed() const;
        STATE GetState() const;
        SIDE GetSide() const;

        void jump();


    private:
        sf::Vector2f speed;
        float jumpAcceleration;
        float gravitation;
        float maxSpeed;

        int state;
        int side;

        sf::Vector2f handleKeys(std::array<bool, KEYS_COUNT> keyState);
        void moveX(SIDE);
        void moveY();

        AnimationController::AnimationController animationController;
    };
}