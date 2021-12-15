//
// Created by sonichka on 28.11.2021.
//

#include "button.h"

GUI::Button::Button(float x, float y, std::string text, std::string pathFont, std::string pathIdleTexture, std::string pathHoverTexture, std::string pathActiveTexture) {
    this->pressed = false;
    this->hover = false;

    this->idleTexture.loadFromFile(pathIdleTexture);
    this->activeTexture.loadFromFile(pathActiveTexture);
    this->hoverTexture.loadFromFile(pathHoverTexture);

    this->sprite.setTexture(this->idleTexture);

    this->sprite.setScale(sf::Vector2f(0.5f, 0.5f));
    sf::Vector2f spriteSize;
    spriteSize.x = float(this->sprite.getTexture()->getSize().x);
    this->sprite.setPosition(x - spriteSize.x/4, y / 2);

    this->font.loadFromFile(pathFont);
}

GUI::Button::~Button() {}

void GUI::Button::Update(sf::Vector2f mousePos) {
    if (this->sprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        this->sprite.setTexture(this->hoverTexture);
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            this->sprite.setTexture(this->activeTexture);
        }
    }
    else {
        this->sprite.setTexture(this->idleTexture);
    }
}

void GUI::Button::Draw(sf::RenderWindow &window) {
    window.draw(this->sprite);
    this->text.setFont(this->font);
    window.draw(this->text);
}
