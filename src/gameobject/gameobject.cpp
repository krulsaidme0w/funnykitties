#include "gameobject.h"

GameObject::GameObject::GameObject() {
    texture = sf::Texture();
    sprite = sf::Sprite();
}

GameObject::GameObject::~GameObject() {

}

void GameObject::GameObject::SetCoordinates(sf::Vector2f coordinates) {
    sprite.setPosition(coordinates);
}

sf::Vector2f GameObject::GameObject::GetCoordinates() {
    return sprite.getPosition();
}

void GameObject::GameObject::SetSprite(sf::Sprite sprite) {
    sprite = sprite;
}

sf::Sprite& GameObject::GameObject::GetSprite() {
    return sprite;
}

void GameObject::GameObject::SetTexture(std::string path) {
    texture.loadFromFile(path);
}

sf::Texture& GameObject::GameObject::GetTexture() {
    return texture;
}
