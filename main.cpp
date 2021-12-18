#include "SFML/Graphics.hpp"
#include "menu.h"
#include "button.h"
#include "iostream"

int main() {
    const int win_width = 1080;
    const int win_height = 1920;

    sf::RenderWindow window(sf::VideoMode(win_height, win_width), "SFML works!");

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