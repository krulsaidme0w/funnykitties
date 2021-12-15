//
// Created by sonichka on 27.11.2021.
//

#include "menu.h"
#include "button.h"

Menu::Menu::Menu(float width, float height) {

    GUI::Button button1 = GUI::Button(width / 2, height / (3 + 1) * 1, "play", "../assets/font/GorgeousPixel.ttf", "../assets/buttons/play.png", "../assets/buttons/mouse_on_play.png", "../assets/buttons/play_pressed.png");
    buttons.push_back(button1);

    GUI::Button button2 = GUI::Button(width / 2, height / (3 + 1) * 2, "options", "../assets/font/GorgeousPixel.ttf", "../assets/buttons/options.png", "../assets/buttons/mouse_on_options.png", "../assets/buttons/options_pressed.png");
    buttons.push_back(button2);

    GUI::Button button3 = GUI::Button(width / 2, height / (3 + 1) * 3, "exit", "../assets/font/GorgeousPixel.ttf", "../assets/buttons/exit.png", "../assets/buttons/mouse_on_exit.png", "../assets/buttons/exit_pressed.png");
    buttons.push_back(button3);

    selectItemIndex = 0;

}

Menu::Menu::~Menu() {

}

void Menu::Menu::Update(sf::RenderWindow &window) {
    auto win_pos = window.getPosition();
    auto mouse_pos = sf::Mouse::getPosition();
    for (auto& button : buttons) {
        button.Update(sf::Vector2f(mouse_pos.x - win_pos.x, mouse_pos.y - win_pos.y - 80));
    }

    menuAction = NONE;
    if (buttons[0].IsPressed()) menuAction = START_GAME;
    if (buttons[2].IsPressed()) menuAction = EXIT_PROGRAM;
}

void Menu::Menu::Draw(sf::RenderWindow &window) {
    for (auto& button : buttons) {
        button.Draw(window);
    }
}
