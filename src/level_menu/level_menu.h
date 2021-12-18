//
// Created by sonichka on 09.12.2021.
//

#ifndef MAIN_CPP_LEVEL_MENU_H
#define MAIN_CPP_LEVEL_MENU_H
#include "vector"
#include "button.h"
#include "SFML/Graphics.hpp"

namespace LM {
    class levelMenu {
    public:
        levelMenu(float width, float height);

        ~levelMenu();

        void Draw(sf::RenderWindow &window);
        void Update();

        int GetPressedItem() { return selectItemIndex; }

    private:
        int selectItemIndex;
        std::vector<GUI::Button> buttons;
        std::vector<GUI::Button> level_buttons;
    };
}

#endif //MAIN_CPP_LEVEL_MENU_H
