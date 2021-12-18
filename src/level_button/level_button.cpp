//
// Created by sonichka on 18.12.2021.
//

#include "level_button.h"

GUI::levelButton::levelButton(float x, float y, std::string level_number, std::string pathFont, std::string pathIdleTexture, std::string pathHoverTexture, std::string pathActiveTexture) {
    pressed = false;
    hover = false;

    font.loadFromFile(pathFont);
    text.setFont(font);
    text.setString(level_number);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(10);
    text.setPosition(
            this->sprite.getPosition().x / 2 - this->text.getGlobalBounds().width / 2.0f,
            this->sprite.getPosition().y / 2 + this->text.getGlobalBounds().height / 2.0f
    );

    idleTexture.loadFromFile(pathIdleTexture);
    activeTexture.loadFromFile(pathActiveTexture);
    hoverTexture.loadFromFile(pathHoverTexture);

    sprite.setTexture(idleTexture);


    sf::Vector2f spriteSize;
//    spriteSize.x = float(sprite.getTexture()->getSize().x);
    sprite.setPosition(x , y);
}

GUI::levelButton::~levelButton() {}

void GUI::levelButton::Update(sf::Vector2f mousePos) {
    if (sprite.getGlobalBounds().contains(mousePos.x, mousePos.y - sprite.getTexture()->getSize().y/4)) {
        sprite.setTexture(hoverTexture);
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sprite.setTexture(activeTexture);
        }
    }
    else {
        sprite.setTexture(idleTexture);
    }
}

void GUI::levelButton::Draw(sf::RenderWindow &window) {
    window.draw(sprite);
    text.setFont(font);
    window.draw(text);
}
