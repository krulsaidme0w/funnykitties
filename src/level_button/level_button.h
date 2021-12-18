//
// Created by sonichka on 18.12.2021.
//

#ifndef MENU_CPP_LEVEL_BUTTON_H
#define MENU_CPP_LEVEL_BUTTON_H


#pragma once
#include "SFML/Graphics.hpp"

namespace GUI {
    class levelButton {
    public:
        levelButton(float x, float y, std::string text, std::string pathFont, std::string pathIdleTexture, std::string pathHoverTexture, std::string pathActiveTexture);
        ~levelButton();

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

#endif //MENU_CPP_LEVEL_BUTTON_H
