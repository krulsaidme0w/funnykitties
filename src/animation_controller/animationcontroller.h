#pragma once

#include "SFML/Graphics.hpp"
#include "vector"
#include "string"

namespace AnimationController {
    class AnimationController {
    public:
        explicit AnimationController();
        ~AnimationController() = default;

        void AddTexture(const std::string& path);
        sf::Texture GetCurrentTexture();

        int GetCurrentTextureIndex() const;
        void SetTextureIndex(int index);
        void SetTextreIndexToNext();
    private:
        int currentIndex;
        std::vector<sf::Texture> textures;
    };
}
