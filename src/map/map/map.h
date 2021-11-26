#pragma once

#include "SFML/Graphics.hpp"
#include "vector"
#include "string"
#include "iostream"

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
    };

    class Map {
    public:
        friend class MapParser;

        explicit Map();
        ~Map();

        void Draw(sf::RenderWindow &window);
        std::vector<sf::Sprite> GetTilesFromLayer(std::string layer);
        std::pair<int, int> GetSize();
        std::pair<int, int> GetTileSize();

    private:
        int width;
        int height;

        int tileWidth;
        int tileHeight;

        int firstID;

        sf::Texture texture;
        sf::Image image;

        std::vector<Layer> layers;
        TileSet tileSet;
    };
}
