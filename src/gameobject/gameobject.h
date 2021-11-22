#pragma once

#include "iostream"
#include "SFML/Graphics.hpp"

namespace GameObject {
      class GameObject {
      public:
          explicit GameObject();
          virtual ~GameObject();

          void SetCoordinates(sf::Vector2f coordinates);
          sf::Vector2f GetCoordinates();

          void SetSprite(sf::Sprite sprite);
          sf::Sprite GetSprite();

          void SetTexture(sf::Texture texture);
          sf::Texture GetTexture();

      protected:
          sf::Sprite sprite;
          sf::Texture texture;
      };
}