#include "animationcontroller.h"

#include "vector"
#include "SFML/Graphics.hpp"

AnimationController::AnimationController::AnimationController() {
    currentWalkIndex = 0;
    addIndex = 0;
    currentTextureState = JUMP;
    walkTextures = std::vector<sf::Texture>(11);
}

void AnimationController::AnimationController::AddWalkTexture(const std::string& path) {
    walkTextures[addIndex++].loadFromFile(path);
}

sf::Texture& AnimationController::AnimationController::GetCurrentTexture() {
    switch (currentTextureState) {
        case FRONT:
            return front;
            break;
        case SIDE:
            return side;
            break;
        case JUMP:
            return jump;
            break;
        case WALK:
            return walkTextures[currentWalkIndex];
            break;
        default:
            return front;
            break;
    }
}

void AnimationController::AnimationController::SetTextureIndexToNext() {
    currentWalkIndex++;
    if(currentWalkIndex > walkTextures.size())
        currentWalkIndex = 0;
}

void AnimationController::AnimationController::SetJumpTexture(const std::string &path) {
    jump.loadFromFile(path);
}

void AnimationController::AnimationController::SetFrontTexture(const std::string &path) {
    front.loadFromFile(path);
}

void AnimationController::AnimationController::SetSideTexture(const std::string &path) {
    side.loadFromFile(path);
}

void AnimationController::AnimationController::SetCurrentTexture(TEXTURE texture) {
    currentTextureState = texture;
}

void AnimationController::AnimationController::Update() {
    SetTextureIndexToNext();
}
