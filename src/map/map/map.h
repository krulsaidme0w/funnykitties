#pragma once

#include "SFML/Graphics.hpp"
#include "vector"

namespace Map {

    struct Object
    {
        int GetPropertyInt(std::string name);
        float GetPropertyFloat(std::string name);
        std::string GetPropertyString(std::string name);

        std::string name;
        std::string type;
        sf::Rect<int> rect;
        std::map<std::string, std::string> properties;

        sf::Sprite sprite;
    };

    struct Layer
    {
        int opacity;
        std::vector<sf::Sprite> tiles;
    };

    class Map {
    public:
        explicit Map();
        ~Map();
        bool LoadFromFile(std::string filename);
        Object GetObject(const std::string& name);
        std::vector<Object> GetObjects(const std::string& name);
        void Draw(sf::RenderWindow &window);
        sf::Vector2i GetTileSize() const;
    private:
        int width;
        int height;
        int tileWidth;
        int tileHeight;
        int firstTileID;
        sf::Rect<float> drawingBounds;
        sf::Texture tileSetImage;
        std::vector<Object> objects;
        std::vector<Layer> layers;
    };
}
