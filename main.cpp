#include "SFML/Graphics.hpp"
#include "menu.h"
#include "button.h"
#include "iostream"

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");

    Menu::Menu menu(window.getSize().x, window.getSize().y);
    sf::Font font;

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

        menu.Draw(window);

        window.display();
    }

}