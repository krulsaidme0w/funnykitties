#pragma once

#include "SFML/Graphics.hpp"
#include "vector"
#include "string"

namespace AnimationController {

    enum TEXTURE {
        FRONT,
        JUMP,
        SIDE,
        WALK
    };

    class AnimationController {
    public:
        explicit AnimationController();
        ~AnimationController() = default;

        void AddWalkTexture(const std::string& path);
        sf::Texture& GetCurrentTexture();

        void SetCurrentTexture(TEXTURE texture);
        void SetJumpTexture(const std::string& path);
        void SetFrontTexture(const std::string& path);
        void SetSideTexture(const std::string& path);
        void Update();
        void SetTextureIndexToNext();
    private:
        TEXTURE currentTextureState;
        int currentWalkIndex;
        int currentClock;
        int addIndex;
        std::vector<sf::Texture> walkTextures;
        sf::Texture front;
        sf::Texture jump;
        sf::Texture side;
    };
}
