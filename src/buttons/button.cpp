//
// Created by sonichka on 28.11.2021.
//

#include "button.h"

GUI::Button::Button(float x, float y, std::string text, std::string pathFont, std::string pathIdleTexture, std::string pathHoverTexture, std::string pathActiveTexture) {
    pressed = false;
    hover = false;

    const float scale_percent = 0.5f;
    const int x_pos = 4;
    const int y_pos = 2;

    idleTexture.loadFromFile(pathIdleTexture);
    activeTexture.loadFromFile(pathActiveTexture);
    hoverTexture.loadFromFile(pathHoverTexture);

    sprite.setTexture(idleTexture);

    sprite.setScale(sf::Vector2f(scale_percent, scale_percent));
    sf::Vector2f spriteSize;
    spriteSize.x = float(sprite.getTexture()->getSize().x);
    sprite.setPosition(x - spriteSize.x / x_pos, y / y_pos);

    font.loadFromFile(pathFont);
}

GUI::Button::~Button() {}

void GUI::Button::Update(sf::Vector2f mousePos) {
<<<<<<< HEAD
    if (sprite.getGlobalBounds().contains(mousePos.x, mousePos.y - sprite.getTexture()->getSize().y/4)) {
        sprite.setTexture(hoverTexture);
=======
    if (this->sprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        this->sprite.setTexture(this->hoverTexture);
>>>>>>> 73a7019573255a45d2004120b34a2607effb35cd
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sprite.setTexture(activeTexture);
        }
    }
    else {
        sprite.setTexture(idleTexture);
    }
}

void GUI::Button::Draw(sf::RenderWindow &window) {
    window.draw(sprite);
    text.setFont(font);
    window.draw(text);
}
