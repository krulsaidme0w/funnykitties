//
// Created by sonichka on 09.12.2021.
//

#include "level_menu.h"
#include "level_button.h"
#include "dir.cpp"
#include "filesystem"

LM::levelMenu::levelMenu(float width, float height) {

    float y_pos = 1;
    int level_number = 1;

    while (true) {
        std::string str_level_num = std::to_string(level_number);

        if (!std::filesystem::exists("level_" + str_level_num)) {
            break;
        }

        if (buttons.size() % 4 == 0) {
            y_pos += 1;
        }

        GUI::levelButton button = GUI::levelButton(width / (buttons.size() % 4), height / (3 + 1) * y_pos, str_level_num, GetExecutableDirectory() + "/assets/font/GorgeousPixel.ttf", GetExecutableDirectory() + "/assets/level_buttons/level_button.png", GetExecutableDirectory() + "/assets/buttons/level_button_highlighted.png", GetExecutableDirectory() + "/assets/buttons/level_button_pressed.png");
        level_buttons.push_back(button);

        level_number++;
    }
    selectItemIndex = 0;

}

LM::levelMenu::~levelMenu() {

}

void LM::levelMenu::Update() {
    for (auto& button : buttons) {
        button.Update(sf::Vector2f(sf::Mouse::getPosition()));
    }
}

void LM::levelMenu::Draw(sf::RenderWindow &window) {
    for (auto& button : buttons) {
        button.Draw(window);
    }
}

