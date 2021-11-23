#include "player.h"

#include "SFML/Graphics.hpp"
#include "cmath"
#include "string"

Player::Player::Player(sf::Vector2f speed, float jumpAcceleration, float gravitation, float maxSpeed, std::string path) {
    this->speed = speed;
    this->gravitation = gravitation;
    this->jumpAcceleration = jumpAcceleration;
    this->maxSpeed = maxSpeed;
    this->state = FALLING;
    this->texture.loadFromFile(path);
    this->sprite.setTexture(this->texture);
}

Player::Player::Player() {
    this->speed = sf::Vector2f(0, 0);
    this->gravitation = 0;
    this->jumpAcceleration = 0;
    this->maxSpeed = 0;
    this->state = 0;
    this->texture = sf::Texture();
    this->sprite = sf::Sprite();
}

Player::Player::~Player() = default;

void Player::Player::Update(std::array<bool, KEYS_COUNT> keyState) {
    handleKeys(keyState);
    moveY();
}

void Player::Player::SetSpeed(sf::Vector2f speed) {
    this->speed = speed;
}

void Player::Player::SetJumpAcceleration(float jumpAcceleration) {
    this->jumpAcceleration = jumpAcceleration;
}

void Player::Player::SetGravitation(float gravitation) {
    this->gravitation = gravitation;
}

void Player::Player::SetMaxSpeed(float maxSpeed) {
    this->maxSpeed = maxSpeed;
}

void Player::Player::SetState(STATE state) {
    this->state = state;
}

sf::Vector2f Player::Player::GetSpeed() const {
    return this->speed;
}

float Player::Player::GetJumpAcceleration() const {
    return this->jumpAcceleration;
}

float Player::Player::GetGravitation() const {
    return this->gravitation;
}

float Player::Player::GetMaxSpeed() const {
    return this->maxSpeed;
}

Player::STATE Player::Player::GetState() const {
    return static_cast<STATE>(this->state);
}


void Player::Player::moveX(SIDE side) {
    if(side == RIGHT) {
        this->sprite.move(speed.x, 0);
    }

    if(side == LEFT) {
        this->sprite.move(-1 * speed.x, 0);
    }
}

void Player::Player::moveY() {
    speed.y += gravitation;

    if(std::abs(speed.y) > maxSpeed) {
        speed.y = -1 * maxSpeed * (std::abs(speed.y) / speed.y);
    }

    if(speed.y > 0) {
        state = FALLING;
    }

    this->sprite.move(0, speed.y);
}

void Player::Player::jump() {
    if(state != JUMPING) {
        speed.y = jumpAcceleration;
        state = JUMPING;
    }
}

void Player::Player::handleKeys(std::array<bool, KEYS_COUNT> keyState) {
    if(keyState[KEY_RIGHT]) {
        moveX(RIGHT);
    }

    if(keyState[KEY_LEFT]) {
        moveX(LEFT);
    }

    if(keyState[KEY_JUMP]) {
        jump();
    }
}
