#include <iostream>
#include "gameobject.h"

GameObject::GameObject::GameObject() {
    this->texture = sf::Texture();
    this->sprite = sf::Sprite();
}

GameObject::GameObject::GameObject(sf::Sprite sprite) {
    this->texture = sf::Texture();
    this->sprite = sprite;
}

GameObject::GameObject::~GameObject() {

}

void GameObject::GameObject::SetCoordinates(sf::Vector2f coordinates) {
    this->sprite.setPosition(coordinates);
}

sf::Vector2f GameObject::GameObject::GetCoordinates() {
    return this->sprite.getPosition();
}

void GameObject::GameObject::SetSprite(sf::Sprite sprite) {
    this->sprite = sprite;
}

sf::Sprite& GameObject::GameObject::GetSprite() {
    return this->sprite;
}

void GameObject::GameObject::SetTexture(std::string path) {
    this->texture.loadFromFile(path);
}

sf::Texture& GameObject::GameObject::GetTexture() {
    return this->texture;
}

void GameObject::GameObject::Draw(sf::RenderWindow &window, sf::Texture &texture, float &map_pos) {
    auto pos = sprite.getPosition();
    sprite.setPosition(pos.x + map_pos, pos.y);
    sprite.setTexture(texture);
    window.draw(sprite);
    sprite.setPosition(pos.x, pos.y);
}
