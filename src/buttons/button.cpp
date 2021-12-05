//
// Created by sonichka on 28.11.2021.
//

#include "button.h"

GUI::Button::Button(float x, float y, std::string text, std::string pathFont, std::string pathIdleTexture, std::string pathActiveTexture) {
    this->pressed = false;
    this->hover = false;

    this->idleTexture.loadFromFile(pathIdleTexture);
    this->activeTexture.loadFromFile(pathActiveTexture);

    this->sprite.setTexture(this->idleTexture);

//    this->sprite.setPosition(x, y);
    this->sprite.setScale(sf::Vector2f(0.5f, 0.5f));
//    sf::Vector2<unsigned int> spriteSize = this->sprite.getTexture()->getSize();
    sf::Vector2f spriteSize;
    spriteSize.x = float(this->sprite.getTexture()->getSize().x);
    this->sprite.setPosition(x - spriteSize.x/4, y / 2);

    this->font.loadFromFile(pathFont);
//    this->text.setString(text);
//    this->text.setCharacterSize(30);
//    this->text.setFillColor(sf::Color::White);
//    this->text.setPosition(
//            this->sprite.getPosition().x + this->sprite.getTexture()->getSize().x / 2 - this->text.,
//            this->sprite.getPosition().y / 2.f - this->text.getPosition().y / 2.f
//    );
}

GUI::Button::~Button() {}

void GUI::Button::Update(sf::Vector2f mousePos) {
    if (this->sprite.getGlobalBounds().contains(mousePos)) {
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
