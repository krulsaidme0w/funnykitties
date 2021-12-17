#pragma once

#include "string"
#include "SFML/Graphics.hpp"

namespace GameObject {

    enum ObjectType{
        NONE,
        SPRING,
        BOX,
        KEY,
        SPIKE,
        KEY_BOX,
        EXIT
    };

      class GameObject {
      public:
          explicit GameObject();
          GameObject(sf::Sprite sprite, ObjectType obj_type = NONE);

          virtual ~GameObject();

          void SetCoordinates(sf::Vector2f coordinates);
          sf::Vector2f GetCoordinates();

          void SetSprite(sf::Sprite sprite);
          sf::Sprite& GetSprite();

          void SetTexture(std::string path);
          sf::Texture& GetTexture();

          virtual void Draw(sf::RenderWindow &window, sf::Texture &, float &map_pos);

          ObjectType type;
      protected:
          sf::Sprite sprite;
          sf::Texture texture;
      };
}