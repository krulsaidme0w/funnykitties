//
// Created by sonichka on 28.11.2021.
//

#include "button.h"
#include "dir.cpp"

GUI::Button::Button(float x, float y, std::string pathIdleTexture, std::string pathHoverTexture, std::string pathActiveTexture) {
    pressed = false;
    hover = false;

    idleTexture.loadFromFile(GetExecutableDirectory() + pathIdleTexture);
    activeTexture.loadFromFile(GetExecutableDirectory() + pathActiveTexture);
    hoverTexture.loadFromFile(GetExecutableDirectory() + pathHoverTexture);

    sprite.setTexture(this->idleTexture);

    sprite.setScale(sf::Vector2f(0.5f, 0.5f));
    sf::Vector2f spriteSize;
    spriteSize.x = float(this->sprite.getTexture()->getSize().x);
    sprite.setPosition(x - spriteSize.x/4, y / 2);
}

GUI::Button::Button(float x, float y, std::string str, std::string pathFont, std::string pathIdleTexture, std::string pathHoverTexture, std::string pathActiveTexture) {
    pressed = false;
    hover = false;

    idleTexture.loadFromFile(GetExecutableDirectory() + pathIdleTexture);
    activeTexture.loadFromFile(GetExecutableDirectory() + pathActiveTexture);
    hoverTexture.loadFromFile(GetExecutableDirectory() + pathHoverTexture);

    sprite.setTexture(idleTexture);

    sprite.setPosition(x , y);
    Move(-1. * (sprite.getTexture()->getSize().x / 2), 0);

    font.loadFromFile(GetExecutableDirectory() + pathFont);
    text.setFont(font);
    text.setString(str);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(100);
    text.setPosition(
            this->sprite.getPosition().x + this->sprite.getTexture()->getSize().x / 2 - text.getGlobalBounds().width / 2.0f,
            this->sprite.getPosition().y + this->text.getGlobalBounds().height / 2.0f
    );
}

GUI::Button::~Button() {}

void GUI::Button::Update(sf::Vector2f mousePos) {
    this->hover = false;
    this->pressed = false;
    if (this->sprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        this->sprite.setTexture(this->hoverTexture);
        this->hover = true;
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            this->sprite.setTexture(this->activeTexture);
            this->pressed = true;
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

sf::Sprite &GUI::Button::GetSprite() {
    return sprite;
}

void GUI::Button::Move(float x, float y) {
    this->sprite.move(x, y);
}
