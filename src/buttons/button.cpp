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

    this->sprite.setPosition(x, y);
    this->sprite.setScale(sf::Vector2f(1.f, 0.4f));
    this->sprite.setPosition(this->sprite.getPosition().x / 2 + 270,
                             this->sprite.getPosition().y / 2
                             );

    this->font.loadFromFile(pathFont);
    this->text.setString(text);
    this->text.setCharacterSize(24);
    this->text.setFillColor(sf::Color::White);
    this->text.setPosition(
            this->text.getPosition().x / 2 + 270,
            this->sprite.getPosition().y / 2.f - this->text.getPosition().y / 2.f
    );
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
