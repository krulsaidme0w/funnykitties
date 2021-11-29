//
// Created by sonichka on 28.11.2021.
//

#include "button.h"

GUI::Button::Button(float x, float y, std::string text, sf::Font font, sf::Texture idleTexture, sf::Texture activeTexture) {
    this->pressed = false;
    this->hover = false;

    this->sprite.setPosition(x, y);
//    this->sprite.setScale(sf::Vector2f(width, height));

    this->font = font;
    this->text.setFont(this->font);
    this->text.setString(text);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(10);
    this->text.setPosition(
            this->sprite.getPosition().x / 2.f - this->text.getGlobalBounds().width / 2.f,
            this->sprite.getPosition().y / 2.f - this->text.getGlobalBounds().height / 2.f
            );

//    this->idleTexture = idleTexture;
//    this->activeTexture = activeTexture;

    this->sprite.setTexture(this->idleTexture, true);

}


GUI::Button::~Button() {}

void GUI::Button::Update(sf::Vector2f mousePos) {
    if (this->sprite.getGlobalBounds().contains(mousePos)) {
        this->sprite.setTexture(this->hoverTexture, true);
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            this->sprite.setTexture(this->activeTexture, true);
        }
    }
}

void GUI::Button::Render(sf::RenderTarget *target) {
    target->draw(this->sprite);
}