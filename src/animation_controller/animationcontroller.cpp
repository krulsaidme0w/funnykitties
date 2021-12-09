#include "animationcontroller.h"

#include "vector"
#include "SFML/Graphics.hpp"

AnimationController::AnimationController::AnimationController() {
    currentIndex = 0;
    textures = std::vector<sf::Texture>{};
}

void AnimationController::AnimationController::AddTexture(const std::string& path) {
    sf::Texture texture;
    texture.loadFromFile(path);
    textures.push_back(texture);
}

sf::Texture AnimationController::AnimationController::GetCurrentTexture() {
    return textures[currentIndex];
}

int AnimationController::AnimationController::GetCurrentTextureIndex() const {
    return currentIndex;
}

void AnimationController::AnimationController::SetTextureIndex(int index) {
    currentIndex = index;
}

void AnimationController::AnimationController::SetTextreIndexToNext() {
    currentIndex++;
    if(currentIndex > textures.size() - 1)
        currentIndex = 0;
}
