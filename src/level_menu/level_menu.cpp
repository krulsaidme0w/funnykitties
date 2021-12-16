//
// Created by sonichka on 09.12.2021.
//

#include "level_menu.h"
#include "button.h"

LM::levelMenu::levelMenu(float width, float height) {

    GUI::Button button1 = GUI::Button(width / 2, height / (3 + 1) * 1, "play", "../assets/font/GorgeousPixel.ttf", "../assets/buttons/play.png", "../assets/buttons/mouse_on_play.png", "../assets/buttons/play_pressed.png");
    buttons.push_back(button1);

    GUI::Button button2 = GUI::Button(width / 2, height / (3 + 1) * 2, "options", "../assets/font/GorgeousPixel.ttf", "../assets/buttons/options.png", "../assets/buttons/mouse_on_options.png", "../assets/buttons/options_pressed.png");
    buttons.push_back(button2);

    GUI::Button button3 = GUI::Button(width / 2, height / (3 + 1) * 3, "exit", "../assets/font/GorgeousPixel.ttf", "../assets/buttons/exit.png", "../assets/buttons/mouse_on_exit.png", "../assets/buttons/exit_pressed.png");
    buttons.push_back(button3);

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

