#include "map.h"

#include "tinyxml2.h"

Map::Map::Map() {

}

Map::Map::~Map() {

}

int Map::Object::GetPropertyInt(std::string name) {
    return atoi(properties[name].c_str());
}

float Map::Object::GetPropertyFloat(std::string name) {
    return strtod(properties[name].c_str(), nullptr);
}

std::string Map::Object::GetPropertyString(std::string name) {
    return properties[name];
}

bool Map::Map::LoadFromFile(std::string filename) {
    tinyxml2::XMLDocument levelFile;

    if (!levelFile.LoadFile(filename.c_str())) {
        return false;
    }

    tinyxml2::XMLElement* map;
    map = levelFile.FirstChildElement("map");

    width = atoi(map->Attribute("width"));
    height = atoi(map->Attribute("height"));
    tileWidth = atoi(map->Attribute("tilewidth"));
    tileHeight = atoi(map->Attribute("tileheight"));

    tinyxml2::XMLElement *tilesetElement;
    tilesetElement = map->FirstChildElement("tileset");
    firstTileID = atoi(tilesetElement->Attribute("firstgid"));

    tinyxml2::XMLElement *image;
    image = tilesetElement->FirstChildElement("image");
    std::string imagepath = image->Attribute("source");

    sf::Image img;

    if (!img.loadFromFile(imagepath)) {
        return false;
    }


    img.createMaskFromColor(sf::Color(109, 159, 185));

    tileSetImage.loadFromImage(img);
    tileSetImage.setSmooth(false);

    int columns = tileSetImage.getSize().x / tileWidth;
    int rows = tileSetImage.getSize().y / tileHeight;

    std::vector<sf::Rect<int>> subRects;

    for (int y = 0; y < rows; y++)
        for (int x = 0; x < columns; x++) {
            sf::Rect<int> rect;

            rect.top = y * tileHeight;
            rect.height = tileHeight;
            rect.left = x * tileWidth;
            rect.width = tileWidth;

            subRects.push_back(rect);
        }

    tinyxml2::XMLElement *layerElement;
    layerElement = map->FirstChildElement("layer");
    while (layerElement) {
        Layer layer;

        if (layerElement->Attribute("opacity") != nullptr) {
            float opacity = strtod(layerElement->Attribute("opacity"), nullptr);
            layer.opacity = 255 * opacity;
        } else {
            layer.opacity = 255;
        }

        tinyxml2::XMLElement *layerDataElement;
        layerDataElement = layerElement->FirstChildElement("data");

        tinyxml2::XMLElement *tileElement;
        tileElement = layerDataElement->FirstChildElement("tile");

        if (tileElement == nullptr) {
            return false;
        }

        int x = 0;
        int y = 0;

        while (tileElement) {
            int tileGID = atoi(tileElement->Attribute("gid"));
            int subRectToUse = tileGID - firstTileID;

            if (subRectToUse >= 0) {
                sf::Sprite sprite;
                sprite.setTexture(tileSetImage);
                sprite.setTextureRect(subRects[subRectToUse]);
                sprite.setPosition(x * tileWidth, y * tileHeight);
                sprite.setColor(sf::Color(255, 255, 255, layer.opacity));

                layer.tiles.push_back(sprite);
            }

            tileElement = tileElement->NextSiblingElement("tile");

            x++;
            if (x >= width) {
                x = 0;
                y++;
                if (y >= height)
                    y = 0;
            }
        }

        layers.push_back(layer);

        layerElement = layerElement->NextSiblingElement("layer");
    }

    tinyxml2::XMLElement *objectGroupElement;

    if (map->FirstChildElement("objectgroup") != nullptr) {
        objectGroupElement = map->FirstChildElement("objectgroup");
        while (objectGroupElement) {
            tinyxml2::XMLElement *objectElement;
            objectElement = objectGroupElement->FirstChildElement("object");

            while (objectElement) {
                std::string objectType;
                if (objectElement->Attribute("type") != nullptr) {
                    objectType = objectElement->Attribute("type");
                }
                std::string objectName;
                if (objectElement->Attribute("name") != nullptr) {
                    objectName = objectElement->Attribute("name");
                }
                int x = atoi(objectElement->Attribute("x"));
                int y = atoi(objectElement->Attribute("y"));

                int width, height;

                sf::Sprite sprite;
                sprite.setTexture(tileSetImage);
                sprite.setTextureRect(sf::Rect<int>(0, 0, 0, 0));
                sprite.setPosition(x, y);

                if (objectElement->Attribute("width") != nullptr) {
                    width = atoi(objectElement->Attribute("width"));
                    height = atoi(objectElement->Attribute("height"));
                } else {
                    width = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].width;
                    height = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].height;
                    sprite.setTextureRect(subRects[atoi(objectElement->Attribute("gid")) - firstTileID]);
                }

                Object object;
                object.name = objectName;
                object.type = objectType;
                object.sprite = sprite;

                sf::Rect<int> objectRect;
                objectRect.top = y;
                objectRect.left = x;
                objectRect.height = height;
                objectRect.width = width;
                object.rect = objectRect;

                tinyxml2::XMLElement *properties;
                properties = objectElement->FirstChildElement("properties");
                if (properties != nullptr) {
                    tinyxml2::XMLElement *prop;
                    prop = properties->FirstChildElement("property");
                    if (prop != nullptr) {
                        while (prop) {
                            std::string propertyName = prop->Attribute("name");
                            std::string propertyValue = prop->Attribute("value");

                            object.properties[propertyName] = propertyValue;

                            prop = prop->NextSiblingElement("property");
                        }
                    }
                }

                objects.push_back(object);

                objectElement = objectElement->NextSiblingElement("object");
            }
            objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
        }
    }

    return true;
}

Map::Object Map::Map::GetObject(const std::string& name) {
    for (auto & object : objects)
        if (object.name == name)
            return object;
}

std::vector<Map::Object> Map::Map::GetObjects(const std::string& name) {
    std::vector<Object> vec;

    for(auto & object : objects)
        if(object.name == name)
            vec.push_back(object);

    return vec;
}

sf::Vector2i Map::Map::GetTileSize() const {
    return sf::Vector2i(tileWidth, tileHeight);
}

void Map::Map::Draw(sf::RenderWindow &window) {
    for(auto & layer : layers)
        for(int tile = 0; tile < layer.tiles.size(); tile++)
            window.draw(layer.tiles[tile]);
}
