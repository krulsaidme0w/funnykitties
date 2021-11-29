#include "map.h"

#include "player.h"

#include "iostream"


Map::Map::Map() {

}

Map::Map::~Map() {

}

void Map::Map::Update(std::array<bool, Player::KEYS_COUNT> keyState, float playerXSpeed) {
    handleKeys(keyState, playerXSpeed);
}

void Map::Map::Draw(sf::RenderWindow &window) {
    for (auto &layer: layers) {
        for (auto &tile: layer.tiles) {
            tile.setTexture(this->texture);
            window.draw(tile);
        }
    }
}

std::vector<sf::Sprite> Map::Map::GetTilesFromLayer(std::string layer) {
    for(auto l : this->layers) {
        if(l.name == layer)
            return l.tiles;
    }
    return std::vector<sf::Sprite>{};
}

std::pair<int, int> Map::Map::GetSize() {
    return std::make_pair(this->width, this->height);
}

std::pair<int, int> Map::Map::GetTileSize() {
    return std::make_pair(this->tileWidth, this->tileHeight);
}

void Map::Map::moveMapX(float deltaX) {
    for(auto& layer : layers) {
        for(sf::Sprite& tile : layer.tiles) {
            tile.move(deltaX, 0);
        }
    }
}

void Map::Map::handleKeys(std::array<bool, Player::KEYS_COUNT> keyState, float playerXSpeed) {
    if(keyState[Player::KEY_RIGHT]) {
        moveMapX(-1 * playerXSpeed);
    }

    if(keyState[Player::KEY_LEFT]) {
        moveMapX(playerXSpeed);
    }
}
