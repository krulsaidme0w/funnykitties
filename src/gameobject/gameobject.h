#pragma once

#include "string"
#include "SFML/Graphics.hpp"

namespace GameObject {
      class GameObject {
      public:
          explicit GameObject();
          GameObject(sf::Sprite sprite);

          virtual ~GameObject();

          void SetCoordinates(sf::Vector2f coordinates);
          sf::Vector2f GetCoordinates();

          void SetSprite(sf::Sprite sprite);
          sf::Sprite& GetSprite();

          void SetTexture(std::string path);
          sf::Texture& GetTexture();

          void Draw(sf::RenderWindow &window, sf::Texture &, float &map_pos);

      protected:
          sf::Sprite sprite;
          sf::Texture texture;
      };
}