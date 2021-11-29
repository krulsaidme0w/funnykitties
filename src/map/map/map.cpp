#include "map.h"

#include "iostream"

Map::Map::Map() {

}

Map::Map::~Map() {

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
