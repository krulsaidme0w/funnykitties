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
        KEY_Z,
        KEYS_COUNT,
    };

    enum SIDE {
        LEFT,
        RIGHT,
        NONE
    };

    enum STATE {
        JUMPING,
        FALLING,
        ON_GROUND,
        STAND
    };

    class Player final : public GameObject::GameObject {
    public:
        explicit Player(sf::Vector2f speed, float jumpAcceleration, float gravitation, float maxSpeed, std::string path);
        explicit Player();
        ~Player() final;

        virtual sf::Vector2f Update(std::array<bool, KEYS_COUNT> keyState);
        //void Draw(sf::RenderWindow& window);
        void Draw(sf::RenderWindow &window, sf::Texture &texture, float &map_pos);

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
        SIDE GetDelta() const;

        void jump();
        void big_jump();


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

        bool changeSide;

        AnimationController::AnimationController animationController;
    };
}