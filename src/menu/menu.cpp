#include "menu.h"

#include "button.h"
#include "gamecontroller.h"
#include "filesystem"

#include "dir.cpp"

#include "SFML/Graphics.hpp"

Menu::Menu::Menu(float width, float height) {

    state = STATE::MAIN;

    initMainButtons(width, height);
    initLevelsButtons(width, height);
}

Menu::Menu::~Menu() {

}

void Menu::Menu::Update(sf::RenderWindow &window) {
    auto win_pos = window.getPosition();
    auto mouse_pos = sf::Mouse::getPosition();
    for (auto& button : mainButtons) {
        button.Update(sf::Vector2f(mouse_pos.x - win_pos.x, mouse_pos.y - win_pos.y));
    }

    menuAction = NONE;
    if (mainButtons[0].IsPressed()) menuAction = START_GAME;
    if (mainButtons[2].IsPressed()) menuAction = EXIT_PROGRAM;


}

void Menu::Menu::Draw(sf::RenderWindow &window) {
    if(state == STATE::MAIN) {
        for (auto& button : mainButtons) {
            button.Draw(window);
        }
    }
    if(state == STATE::LEVELS) {

    }
}

void Menu::Menu::Run(sf::RenderWindow &window) {
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
        Update(window);

        switch(menuAction) {
            case Actions::START_GAME:
                {
//                    GameController::GameController *gameController = new GameController::GameController();
//                    gameController->Run(window);
//                    delete gameController;
                    state = STATE::LEVELS;
                }
                break;
            case Actions::EXIT_PROGRAM:
                window.close();
                break;
            case NONE:
                break;
            default:
                break;
        }

        Draw(window);
        window.display();
    }
}

void Menu::Menu::initMainButtons(float width, float height) {
    GUI::Button button1 = GUI::Button(width / 2, height / (3 + 1) * 1, "play", "../assets/font/GorgeousPixel.ttf", "../assets/buttons/play.png", "../assets/buttons/mouse_on_play.png", "../assets/buttons/play_pressed.png");
    mainButtons.push_back(button1);

    GUI::Button button2 = GUI::Button(width / 2, height / (3 + 1) * 2, "options", "../assets/font/GorgeousPixel.ttf", "../assets/buttons/options.png", "../assets/buttons/mouse_on_options.png", "../assets/buttons/options_pressed.png");
    mainButtons.push_back(button2);

    GUI::Button button3 = GUI::Button(width / 2, height / (3 + 1) * 3, "exit", "../assets/font/GorgeousPixel.ttf", "../assets/buttons/exit.png", "../assets/buttons/mouse_on_exit.png", "../assets/buttons/exit_pressed.png");
    mainButtons.push_back(button3);
}

void Menu::Menu::initLevelsButtons(float width, float height) {
    levelsNames = getLevelsNames(GetExecutableDirectory() + "/levels/");

    for(const auto& levelName : levelsNames) {

        //levelButtons.push_back(asdasd)
    }
}

std::vector<std::string> Menu::Menu::getLevelsNames(std::string path) {
    std::vector<std::string> dirNames;
    for ( const auto & entry : std::filesystem::directory_iterator(path)) {
        dirNames.push_back(entry.path());
    }
    return dirNames;
}
