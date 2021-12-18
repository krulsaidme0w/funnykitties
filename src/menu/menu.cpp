#include "menu.h"

#include "button.h"
#include "gamecontroller.h"
#include "filesystem"
#include "SFML/Graphics.hpp"

Menu::Menu::Menu(float width, float height) {

    state = STATE::MAIN;
    levelToStart = -1;

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

    for (auto& button : levelButtons) {
        button.Update(sf::Vector2f(mouse_pos.x - win_pos.x, mouse_pos.y - win_pos.y));
    }

    bool changed = false;
    menuAction = NONE;
    if (mainButtons[0].IsPressed()) {
        menuAction = START_GAME;
        changed = true;
    }
    if (mainButtons[2].IsPressed()) menuAction = EXIT_PROGRAM;

    for(auto i = 0; i < levelButtons.size(); ++i) {
        if(levelButtons[i].IsPressed() && state == STATE::LEVELS && !changed) {
            levelToStart = i;
            menuAction = START_LEVEL;
        }
    }

}

void Menu::Menu::Draw(sf::RenderWindow &window) {
    if(state == STATE::MAIN) {
        for (auto& button : mainButtons) {
            button.Draw(window);
        }
    }
    if(state == STATE::LEVELS) {
        for (auto& button : levelButtons) {
            button.Draw(window);
        }
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
                state = STATE::LEVELS;
                break;
            case Actions::START_LEVEL:
            {
                    auto *gameController = new GameController::GameController(levelsNames[levelToStart] + "/map.json");
                    gameController->Run(window);
                    delete gameController;
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
    GUI::Button button1 = GUI::Button(width / 2, height / (3 + 1) * 1, "/assets/buttons/play.png", "/assets/buttons/mouse_on_play.png", "/assets/buttons/play_pressed.png");
    mainButtons.push_back(button1);

    GUI::Button button2 = GUI::Button(width / 2, height / (3 + 1) * 2, "/assets/buttons/options.png", "/assets/buttons/mouse_on_options.png", "/assets/buttons/options_pressed.png");
    mainButtons.push_back(button2);

    GUI::Button button3 = GUI::Button(width / 2, height / (3 + 1) * 3, "/assets/buttons/exit.png", "/assets/buttons/mouse_on_exit.png", "/assets/buttons/exit_pressed.png");
    mainButtons.push_back(button3);
}

void Menu::Menu::initLevelsButtons(float width, float height) {
    levelsNames = getLevelsNames( "../levels/");

    float y_pos = 0;
    int levelNum = 1;
    float offset = 60;

    for(const auto& levelName : levelsNames) {
        std::string str_level_num = std::to_string(levelNum);

        GUI::Button button = GUI::Button(width / 2, height / (2 + 1) * y_pos + offset, str_level_num, "/assets/font/GorgeousPixel.ttf", "/assets/level_buttons/level_button.png", "/assets/level_buttons/level_button_highlighted.png", "/assets/level_buttons/level_button_pressed.png");

        levelButtons.push_back(button);


        y_pos++;
        levelNum++;
    }

}

std::vector<std::string> Menu::Menu::getLevelsNames(std::string path) {
    std::vector<std::string> dirNames;
    for ( const auto & entry : std::filesystem::directory_iterator(path)) {
        dirNames.push_back(entry.path());
    }
    return dirNames;
}
