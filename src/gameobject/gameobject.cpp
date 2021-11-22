#include "gameobject.h"

GameObject::GameObject::GameObject() {
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

sf::Sprite GameObject::GameObject::GetSprite() {
    return this->sprite;
}

void GameObject::GameObject::SetTextue(sf::Texture) {
    this->texture = texture;
}

sf::Texture GameObject::GameObject::GetTexture() {
    return this->texture;
}
