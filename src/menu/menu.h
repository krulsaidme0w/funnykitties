//
// Created by sonichka on 27.11.2021.
//

#ifndef PROJECT_MENU_H
#define PROJECT_MENU_H
#pragma once
#include "SFML/Graphics.hpp"
#include "vector"
#include "button.h"

#define MAX_NUMBER_OF_ITEMS 3

namespace Menu {
    class Menu {
    public:
        Menu(unsigned int width, unsigned int height);

        ~Menu();

        void Draw(sf::RenderWindow &window);

        void MoveUp();

        void MoveDown();

        int GetPressedItem() { return selectItemIndex; }

    private:
        int selectItemIndex;
        sf::Font font;
//        sf::Text menu[MAX_NUMBER_OF_ITEMS];
        std::vector<GUI::Button> menu;
        sf::Texture idleTexture;
        sf::Texture activeTexture;
    };
}


#endif //PROJECT_MENU_H
