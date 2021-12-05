//
// Created by sonichka on 27.11.2021.
//

#include "menu.h"
#include "button.h"

Menu::Menu::Menu(float width, float height) {

    GUI::Button button1 = GUI::Button(width / 2, height / (3 + 1) * 1, "play", "../assets/font/GorgeousPixel.ttf", "../assets/buttons/play.png", "../assets/buttons/Button_Dark_Pressed.png");
    buttons.push_back(button1);

    GUI::Button button2 = GUI::Button(width / 2, height / (3 + 1) * 2, "options", "../assets/font/GorgeousPixel.ttf", "../assets/buttons/options.png", "../assets/buttons/Button_Dark_Pressed.png");
    buttons.push_back(button2);

    GUI::Button button3 = GUI::Button(width / 2, height / (3 + 1) * 3, "exit", "../assets/font/GorgeousPixel.ttf", "../assets/buttons/exit.png", "../assets/buttons/Button_Dark_Pressed.png");
    buttons.push_back(button3);

    selectItemIndex = 0;

}

Menu::Menu::~Menu() {

}

void Menu::Menu::Update() {
    for (auto& button : buttons) {
        button.Update(sf::Vector2f(0,0));
    }
}

void Menu::Menu::Draw(sf::RenderWindow &window) {
    for (auto& button : buttons) {
        button.Draw(window);
    }
}
