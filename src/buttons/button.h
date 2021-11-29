#pragma once
#include "SFML/Graphics.hpp"

namespace GUI {
    class Button {
    public:
        Button(float x, float y, std::string text, sf::Font font, sf::Texture idleTexture, sf::Texture activeTexture);
        ~Button();

        void Update(sf::Vector2f mousePos);
        void MouseEvent(sf::Event &event);
        void Render(sf::RenderTarget* target);

    private:
        bool pressed;
        bool hover;

        sf::Sprite sprite;
        sf::Font font;
        sf::Text text;

        sf::Texture idleTexture;
        sf::Texture hoverTexture;
        sf::Texture activeTexture;


//        sf::Sprite activeSprite;
//        sf::Color idleColor;
//        sf::Color hoverColor;
//        sf::Color activeColor;
    };
}
