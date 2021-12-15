#include "gamecontroller.h"

#include "SFML/Graphics.hpp"
#include "menu.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "PLAYER_TEST");
    window.setFramerateLimit(120);

    Menu::Menu menu(window.getSize().x, window.getSize().y);
    sf::Font font;

    GameController::GameController *gameController;


    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();

                    break;
            }
        }

        window.clear();
        menu.Update(window);

        switch (menu.menuAction) {
            case Menu::Actions::START_GAME:
                gameController = new GameController::GameController();
                gameController->Run(window);
                delete gameController;
                break;
            case Menu::Actions::EXIT_PROGRAM:
                window.close();
                break;
        }

        menu.Draw(window);
        window.display();
    }

    return 0;
}