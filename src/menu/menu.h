//
// Created by sonichka on 27.11.2021.
//
#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include "vector"
#include "button.h"

namespace Menu {
    enum Actions{
        START_GAME,
        EXIT_PROGRAM,
        NONE
    };

    class Menu {
    public:
        Menu(float width, float height);

        ~Menu();

        void Draw(sf::RenderWindow &window);
        void Update(sf::RenderWindow &window);

        int GetPressedItem() { return selectItemIndex; }

        Actions menuAction;
    private:
        int selectItemIndex;
        std::vector<GUI::Button> buttons;
    };
}


