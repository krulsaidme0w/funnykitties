#include "gamecontroller.h"

#include "SFML/Graphics.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 800), "PLAYER_TEST");
    window.setFramerateLimit(120);

    GameController::GameController gameController = GameController::GameController();
    gameController.Run(window);
}