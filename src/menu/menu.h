//
// Created by sonichka on 27.11.2021.
//
#pragma once
#include "SFML/Graphics.hpp"
#include "vector"
#include "button.h"

namespace Menu {
    class Menu {
    public:
        Menu(float width, float height);

        ~Menu();

        void Draw(sf::RenderWindow &window);
        void Update();

//        void MoveUp();
//
//        void MoveDown();

        int GetPressedItem() { return selectItemIndex; }

    private:
        int selectItemIndex;
        std::vector<GUI::Button> buttons;
    };
}


