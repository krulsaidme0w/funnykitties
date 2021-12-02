#include "SFML/Graphics.hpp"
#include "menu.h"
#include "button.h"
#include "iostream"

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");

    Menu::Menu menu(window.getSize().x, window.getSize().y);
    sf::Font font;
//    sf::Text txt;
//
//    font.loadFromFile("../assets/font/GorgeousPixel.ttf");
//
//    txt.setFont(font);
//
//    txt.setCharacterSize(120);
//    txt.setString("SFML Basic");

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            switch (event.type) {
//                case sf::Event::KeyReleased:
//                    switch (event.key.code)
//                    {
//                        case sf::Keyboard::Up:
//                            menu.MoveUp();
//                            break;
//
//                        case sf::Keyboard::Down:
//                            menu.MoveDown();
//                            break;
//
//                        case sf::Keyboard::Return:
//                            switch (menu.GetPressedItem()) {
//                                case 0:
//                                    std::cout << "1" << std::endl;
//                                    break;
//                                case 1:
//                                    std::cout << "2" << std::endl;
//                                    break;
//                                case 2:
//                                    std::cout << "exit";
//                                    window.close();
//                                    break;
//                            }
//
//                            break;
//                    }
//
//                    break;

                case sf::Event::Closed:
                    window.close();

                    break;
            }
        }

        menu.Update();

        menu.Draw(window);

//        window.draw(txt);

        window.display();
    }

}