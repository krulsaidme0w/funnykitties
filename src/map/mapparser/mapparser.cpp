#include "mapparser.h"

#include "nlohmann/json.hpp"
#include "fstream"


#include "iostream"

Map::Map Map::MapParser::GetMap(const std::string& path) {

    std::ifstream in(path);
    nlohmann::json json = nlohmann::json::parse(in);

    Map map = Map();

    map.width = json["width"];
    map.height = json["height"];
    map.tileWidth = json["tilewidth"];
    map.tileHeight = json["tileheight"];

    std::string tileSetPath;
    for(auto& elem : json["tilesets"]) {
        tileSetPath = elem["source"];
        map.firstID = elem["firstgid"];
        break;
    }

    std::ifstream i(tileSetPath);
    nlohmann::json tileSetJson = nlohmann::json::parse(i);

    TileSet tileSet;
    tileSet.path = tileSetJson["image"];

    map.image.loadFromFile(tileSet.path);

    map.texture.loadFromImage(map.image);

    tileSet.columns = map.texture.getSize().x / map.tileWidth;
    tileSet.rows = map.texture.getSize().y / map.tileHeight;

    tileSet.rects = std::vector<sf::Rect<int>>{};
    for(int y = 0; y < tileSet.rows; ++y) {
        for(int x = 0; x < tileSet.columns; ++x) {
            sf::Rect<int> rect;

            rect.top = y * map.tileHeight;
            rect.height = map.tileHeight;
            rect.left = x * map.tileWidth;
            rect.width = map.tileWidth;

            tileSet.rects.push_back(rect);
        }
    }

    map.tileSet = tileSet;

    map.layers = std::vector<Layer>{};
    for(auto& elem : json["layers"]) {
        Layer layer;

        layer.name = elem["name"];

        layer.opacity = 255;
        if(elem["opacity"] != 1) {
            layer.opacity = elem["opacity"];
        }

        std::vector<int> data = std::vector<int>{};
        int x = 0;
        int y = 0;
        for(const auto& num : elem["data"]) {
            if(int(num) != 0) {
                int index = int(num) - map.firstID;

                sf::Sprite sprite;
                sprite.setTexture(map.texture);
                sprite.setTextureRect(tileSet.rects[index]);
                sprite.setPosition(x * map.tileWidth, y * map.tileHeight);
                sprite.setColor(sf::Color(255, 255, 255, layer.opacity));

                layer.tiles.push_back(sprite);
                layer.id.push_back(num);
            }

            x++;
            if (x >= map.width) {
                x = 0;
                y++;
                if(y >= map.height)
                    y = 0;
            }
        }

        map.layers.push_back(layer);
    }

    return map;
}

std::vector<GameObject::GameObject*> Map::MapParser::GetObjects(Map &map) {
    std::vector<GameObject::GameObject*> gameObjects;
    for (auto &layer : map.layers){
        if (layer.name != "item") continue;
        for (int i = 0; i < layer.tiles.size(); i++){
            if (layer.id[i] == 125) {
                Item::Spring *spring = new Item::Spring(layer.tiles[i]);
                gameObjects.push_back(spring);
                continue;
            }

            if (layer.id[i] == 145) {
                Item::Box *box = new Item::Box(layer.tiles[i]);
                gameObjects.push_back(box);
                continue;
            }
        }
    }
    return gameObjects;
}
