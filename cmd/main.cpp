#include "gamecontroller.h"

#include "SFML/Graphics.hpp"
#include "menu.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "PLAYER_TEST");
    window.setFramerateLimit(120);

    Menu::Menu menu(window.getSize().x, window.getSize().y);

    menu.Run(window);

    return 0;
}