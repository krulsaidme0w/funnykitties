#pragma once
#include "SFML/Graphics.hpp"

namespace GUI {
    class Button {
    public:
        Button(float x, float y, std::string text, std::string pathFont, std::string pathIdleTexture, std::string pathActiveTexture);
        ~Button();

        void Update(sf::Vector2f mousePos);
        void MouseEvent(sf::Event &event);
        void Draw(sf::RenderWindow &window);

    private:
        bool pressed;
        bool hover;

        sf::Texture idleTexture;
        sf::Texture hoverTexture;
        sf::Texture activeTexture;

        sf::Sprite sprite;
        sf::Font font;
        sf::Text text;
    };
}
