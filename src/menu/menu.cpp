//
// Created by sonichka on 27.11.2021.
//

#include "menu.h"
#include "button.h"
#include "dir.cpp"

Menu::Menu::Menu(float width, float height) {

    const int width_divider = 2;
    const int height_divider = (3 + 1);

    GUI::Button button1 = GUI::Button(width / width_divider, height / height_divider * 1, GetExecutableDirectory() + "/assets/buttons/play.png",  GetExecutableDirectory() +  "/assets/buttons/mouse_on_play.png", GetExecutableDirectory() + "/assets/buttons/play_pressed.png");
    buttons.push_back(button1);

    GUI::Button button2 = GUI::Button(width / width_divider, height / height_divider * 2, GetExecutableDirectory() + "/assets/buttons/options.png", GetExecutableDirectory() + "/assets/buttons/mouse_on_options.png", GetExecutableDirectory() + "/assets/buttons/options_pressed.png");
    buttons.push_back(button2);

    GUI::Button button3 = GUI::Button(width / width_divider, height / height_divider * 3, GetExecutableDirectory() + "/assets/buttons/exit.png", GetExecutableDirectory() + "/assets/buttons/mouse_on_exit.png", GetExecutableDirectory() + "/assets/buttons/exit_pressed.png");
    buttons.push_back(button3);

    selectItemIndex = 0;

}

Menu::Menu::~Menu() {

}

void Menu::Menu::Update(sf::RenderWindow &window) {
    for (auto& button : buttons) {
        button.Update(sf::Vector2f(sf::Mouse::getPosition()));
    }
}

void Menu::Menu::Draw(sf::RenderWindow &window) {
    for (auto& button : buttons) {
        button.Draw(window);
    }
}
