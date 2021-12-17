#include "player.h"

#include "SFML/Graphics.hpp"
#include "cmath"
#include "string"


Player::Player::Player(sf::Vector2f _speed, float _jumpAcceleration, float _gravitation, float _maxSpeed, std::string _path) {
    speed = _speed;
    gravitation = _gravitation;
    jumpAcceleration = _jumpAcceleration;
    maxSpeed = _maxSpeed;
    state = FALLING;
    changeSide = false;
    texture.loadFromFile("../assets/player/front.png");
    animationController = AnimationController::AnimationController();
    animationController.SetFrontTexture("../assets/player/front.png");
    animationController.SetJumpTexture("../assets/player/jump.png");
    animationController.SetSideTexture("../assets/player/side.png");
    for(int i = 1; i < 12; ++i) {
        animationController.AddWalkTexture("../assets/player/walk/" + std::to_string(i) + ".png");
    }

//    sprite.setTextureRect(sf::Rect(0, 0, 66,92));
    //sprite.setTexture(texture);
    sprite.setTexture(animationController.GetCurrentTexture());
}

Player::Player::Player() {
    speed = sf::Vector2f(0, 0);
    gravitation = 0;
    jumpAcceleration = 0;
    maxSpeed = 0;
    state = FALLING;
    animationController = AnimationController::AnimationController();
    animationController.SetFrontTexture("../assets/player/front.png");
    animationController.SetJumpTexture("../assets/player/jump.png");
    animationController.SetSideTexture("../assets/player/side.png");
    for(int i = 1; i < 12; ++i) {
        animationController.AddWalkTexture("../assets/player/walk/" + std::to_string(i) + ".png");
    }

    sprite.setTexture(animationController.GetCurrentTexture());
}

Player::Player::~Player() = default;

sf::Vector2f Player::Player::Update(std::array<bool, KEYS_COUNT> keyState) {

    int oldSide = side;
    sf::Vector2f delta = handleKeys(keyState);

    moveY();

    if (delta.x > 0) moveX(RIGHT);
    if (delta.x < 0) moveX(LEFT);

    switch (state) {
        case JUMPING:
            animationController.SetCurrentTexture(AnimationController::JUMP);
            break;
        case ON_GROUND:
            if (delta.x == 0) animationController.SetCurrentTexture(AnimationController::FRONT);
            else animationController.SetCurrentTexture(AnimationController::WALK);
            break;
        case FALLING:
            animationController.SetCurrentTexture(AnimationController::FRONT);
            break;
        default:
            break;
    }

     animationController.Update();

    texture = animationController.GetCurrentTexture();
    return delta;
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
    return speed;
}

float Player::Player::GetJumpAcceleration() const {
    return jumpAcceleration;
}

float Player::Player::GetGravitation() const {
    return gravitation;
}

float Player::Player::GetMaxSpeed() const {
    return maxSpeed;
}

Player::STATE Player::Player::GetState() const {
    return static_cast<STATE>(state);
}

Player::SIDE Player::Player::GetSide() const {
    return static_cast<SIDE>(side);
}

void Player::Player::moveX(SIDE side) {
    side = side;
    if(side == RIGHT) {
        sprite.move(speed.x, 0);
    }

    if(side == LEFT) {
        sprite.move(-1 * speed.x, 0);
    }
}

void Player::Player::moveY() {
    speed.y += gravitation;

    if(std::abs(speed.y) > maxSpeed) {
        speed.y = -1 * maxSpeed * (std::abs(speed.y) / speed.y);
    }

    if(speed.y > 1) {
        state = FALLING;
    }

    sprite.move(0, speed.y);
}

void Player::Player::jump() {
    if(state == ON_GROUND) {
        speed.y = jumpAcceleration;
        state = JUMPING;
    }
}

void Player::Player::big_jump() {
    if(state == ON_GROUND) {
        speed.y = 1.7 * jumpAcceleration;
        state = JUMPING;
    }
}

sf::Vector2f Player::Player::handleKeys(std::array<bool, KEYS_COUNT> keyState) {

    sf::Vector2f delta;
    delta.x = 0;
    delta.y = 0;

    if(keyState[KEY_RIGHT]) {
        delta.x = 1;
        if (side != RIGHT) changeSide = true;
        side = RIGHT;
    }

    if(keyState[KEY_LEFT]) {
        delta.x = -1;
        if (side != LEFT) changeSide = true;
        side = LEFT;
    }

    if(keyState[KEY_JUMP]) {
        jump();
    }

    return delta;
}

//void Player::Player::Draw(sf::RenderWindow& window) {
//    sprite.setTexture(animationController.GetCurrentTexture());
//    window.draw(sprite);
//}


void Player::Player::Draw(sf::RenderWindow &window, sf::Texture &texture, float &map_pos) {
    sprite.move(-map_pos, 0);

    sprite.setTexture(texture, true);
    auto tex_size = texture.getSize();
    if (side == LEFT){
        sprite.setTextureRect(sf::IntRect(tex_size.x, 0, -tex_size.x, tex_size.y));
    } else {
        sprite.setTextureRect(sf::IntRect(0, 0, tex_size.x, tex_size.y));
    }
    window.draw(sprite);

    sprite.move(map_pos, 0);
}