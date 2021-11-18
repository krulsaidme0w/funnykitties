#include "SFML/Graphics/Drawable.hpp"

namespace gui {

class Button : public sf::Drawable {
 public:
  Button();
  ~Button();
  void update(sf::Event &e, sf::RenderWindow &window);

 private:
};

}  // namespace gui