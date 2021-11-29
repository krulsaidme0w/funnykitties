//
// Created by sonichka on 27.11.2021.
//

#include "menu.h"
#include "button.h"

Menu::Menu::Menu(unsigned int width, unsigned int height) {
    if(!font.loadFromFile("../../font/GorgeousPixel.ttf")){
        return;
    }

    if(!idleTexture.loadFromFile("../../buttons texture/Button_Dark.png")) {
        return;
    }

    if(!idleTexture.loadFromFile("../../buttons texture/Button_Dark_Pressed.png")) {
        return;
    }

    menu[0](width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1), "PLAY", font, idleTexture, activeTexture)
    menu[0](width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2), "OPTIONS", font, idleTexture, activeTexture)
    menu[0](width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 3), "EXIT", font, idleTexture, activeTexture)
//    menu[0].setFont(font);
//    menu[0].setFillColor(sf::Color::Red);
//    menu[0].setString("Play");
//    menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));
//
//    menu[1].setFont(font);
//    menu[1].setFillColor(sf::Color::White);
//    menu[1].setString("Options");
//    menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));
//
//    menu[2].setFont(font);
//    menu[2].setFillColor(sf::Color::White);
//    menu[2].setString("Exit");
//    menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

    selectItemIndex = 0;

}

Menu::Menu::~Menu() {

}

void Menu::Menu::Draw(sf::RenderWindow &window){
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
        window.draw(menu[i]);
    }
}

//void Menu::Menu::MoveUp() {
//    if (selectItemIndex - 1 >= 0) {
//        menu[selectItemIndex].setColor(sf::Color::White);
//        selectItemIndex--;
//        menu[selectItemIndex].setColor(sf::Color::Red);
//    }
//}
//
//void Menu::Menu::MoveDown() {
//    if (selectItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {
//        menu[selectItemIndex].setColor(sf::Color::White);
//        selectItemIndex++;
//        menu[selectItemIndex].setColor(sf::Color::Red);
//    }
}