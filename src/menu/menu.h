//
// Created by sonichka on 27.11.2021.
//
#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include "vector"
#include "button.h"
#include "string"


namespace Menu {
    enum Actions{
        START_GAME,
        EXIT_PROGRAM,
        NONE
    };

    enum class STATE {
        MAIN,
        LEVELS
    };

    class Menu {
    public:
        Menu(float width, float height);

        ~Menu();

        void Draw(sf::RenderWindow& window);
        void Update(sf::RenderWindow& window);
        void Run(sf::RenderWindow& window);


        int GetPressedItem() { return selectItemIndex; }

        Actions menuAction;
    private:
        std::vector<std::string> getLevelsNames(std::string path);
        void initLevelsButtons(float width, float height);
        void initMainButtons(float width, float height);
        std::vector<std::string> levelsNames;
        STATE state;
        int selectItemIndex;
        std::vector<GUI::Button> mainButtons;
        std::vector<GUI::Button> levelButtons;

    };
}


