#pragma once

#include "player.h"

#include "SFML/Graphics.hpp"
#include "vector"
#include "string"
#include "iostream"
#include "array"

namespace Map {

    struct TileSet {
        std::string path;
        int columns;
        int rows;
        std::vector<sf::Rect<int>> rects;
    };

    struct Layer {
        int opacity;
        std::string name;
        std::vector<sf::Sprite> tiles;
        std::vector<int> id;
    };

    class Map {
    public:
        friend class MapParser;

        explicit Map();
        ~Map();

        void Update(std::array<bool, Player::KEYS_COUNT> keyState, float playerXSpeed);
        void Draw(sf::RenderWindow &window);
        void MoveX(float x);

        std::vector<sf::Sprite> GetTilesFromLayer(std::string layer);
        std::pair<int, int> GetSize();
        std::pair<int, int> GetTileSize();

        sf::Texture texture;
        float x;

    private:

        int width;
        int height;

        int tileWidth;
        int tileHeight;

        int firstID;

        sf::Image image;

        std::vector<Layer> layers;
        TileSet tileSet;

        void moveMapX(float deltaX);
        void handleKeys(std::array<bool, Player::KEYS_COUNT> keyState, float playerXSpeed);
    };
}
