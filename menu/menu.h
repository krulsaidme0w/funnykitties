//
// Created by sonichka on 27.11.2021.
//

#ifndef PROJECT_MENU_H
#define PROJECT_MENU_H
#pragma once
#include "SFML/Graphics.hpp"

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
        sf::Text menu[MAX_NUMBER_OF_ITEMS];
    };
}


#endif //PROJECT_MENU_H
