#include "gamecontroller.h"

GameController::GameController::GameController(std::string levelMap) {
    initPlayer();
    Map::MapParser parser = Map::MapParser();
    map = parser.GetMap(levelMap);
    gameObjects = parser.GetObjects(map);

    keyState = std::array<bool, Player::KEYS_COUNT>{false, false, false};
    gameStatus = 0;
}

GameController::GameController::~GameController() {
    delete player;
}

void GameController::GameController::Run(sf::RenderWindow& window) {
    while(window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                return;

            handleKeys(event);
        }

        if (gameStatus != 0) {
            if (gameStatus == -1) window.clear(sf::Color(255, 150, 150, 200));
            if (gameStatus == 1) window.clear(sf::Color(150, 255, 150, 100));
            window.display();
            sleep(1);
            return;
        }

        window.clear(sf::Color(56, 53, 53, 255));

        //map.Update(keyState, this->player->GetSpeed().x);

        sf::Vector2f delta = player->Update(keyState);
        keyState[Player::KEY_JUMP] = false;

        checkCollisionWithPlatforms(delta);
        checkCollisionWithObjects(delta);
        checkCollisionBetweenObjects();

        map.position = player->GetCoordinates().x - 1920 / 2;

        map.Draw(window);
        for (auto &object : gameObjects){
           object->Draw(window, map.texture, map.position);
        }

        //dynamic_cast<GameObject::GameObject*>(player)->Draw(window, player->GetTexture(), map.position);
        player->Draw(window, player->GetTexture(), map.position);
        window.display();
    }
}

void GameController::GameController::initPlayer() {
    sf::Vector2f speed;
    speed.x = 2;
    speed.y = 0;
    float jumpAcceleration = -7;
    float gravitation = 0.20;
    float maxSpeed = 100;
    std::string path = "../assets/player/cat.png";

    player = new Player::Player(speed, jumpAcceleration, gravitation, maxSpeed, path);
    player->SetCoordinates(sf::Vector2f(1920 / 2, 100));

}

void GameController::GameController::handleKeys(sf::Event& event) {

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        keyState[Player::KEY_LEFT] = true;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        keyState[Player::KEY_RIGHT] = true;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        keyState[Player::KEY_JUMP] = true;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        keyState[Player::KEY_Z] = true;
    }

    if (event.type == sf::Event::KeyReleased) {
        switch(event.key.code){
            case sf::Keyboard::A:{
                keyState[Player::KEY_LEFT] = false;
                break;
            }
            case sf::Keyboard::D:{
                keyState[Player::KEY_RIGHT] = false;
                break;
            }
            case sf::Keyboard::Space: {
                keyState[Player::KEY_JUMP] = false;
                break;
            }
            case sf::Keyboard::Z: {
                keyState[Player::KEY_Z] = false;
                break;
            }

            default:
                break;
        }
    }
}

void GameController::GameController::checkCollisionWithPlatforms(sf::Vector2f delta) {
    sf::Vector2u playerSize = player->GetSprite().getTexture()->getSize();
    std::pair<int, int> tileSize = map.GetTileSize();
    std::vector<sf::Sprite> tiles = map.GetTilesFromLayer("platform");

    for(auto& tile : tiles) {
        if(player->GetSprite().getGlobalBounds().intersects(tile.getGlobalBounds())) {

            sf::Vector2f speed = player->GetSpeed();

            if(speed.y < 0 && player->GetCoordinates().y > tile.getPosition().y && delta.x == 0) {
                player->SetCoordinates(sf::Vector2f(player->GetCoordinates().x, tile.getPosition().y + tileSize.second));
            }

            if(speed.y > 0 && player->GetCoordinates().y + playerSize.y < tile.getPosition().y + playerSize.y) {
                player->SetCoordinates(sf::Vector2f(player->GetCoordinates().x, tile.getPosition().y - playerSize.y));
                player->SetState(Player::ON_GROUND);
                player->SetSpeed(sf::Vector2f(speed.x, 0));
            }
        }

        if(player->GetSprite().getGlobalBounds().intersects(tile.getGlobalBounds())) {
            if (delta.x == -1) {
                player->SetCoordinates(sf::Vector2f(tile.getPosition().x + tileSize.first, player->GetCoordinates().y));
                //player->SetCoordinates(, player->GetCoordinates().y);
                //this->map.MoveX(-1 * (tile.getPosition().x + tileSize.first - player->GetCoordinates().x));
            }

            if (delta.x == 1) {
                player->SetCoordinates(sf::Vector2f(tile.getPosition().x - playerSize.x, player->GetCoordinates().y));
                //this->map.MoveX(player->GetCoordinates().x + playerSize.x - tile.getPosition().x);
            }
        }
    }
}

void GameController::GameController::checkCollisionWithObjects(sf::Vector2f delta) {

//    sf::Vector2u playerSize = player->GetSprite().getTexture()->getSize();
//    std::pair<int, int> tileSize = map.GetTileSize();
//    std::vector<sf::Sprite> tiles = map.GetTilesFromLayer("platform");

    for(auto& object : gameObjects) {

        switch (object->type){
            case GameObject::SPRING:
                //auto spring = dynamic_cast<Item::Spring*>(object);
                dynamic_cast<Item::Spring*>(object)->CollisionPlayer(player, delta);
                break;
            case GameObject::BOX:
                dynamic_cast<Item::Box*>(object)->CollisionPlayer(player, delta);
                break;
            case GameObject::KEY:
                dynamic_cast<Item::Key*>(object)->CollisionPlayer(player, delta);
                break;
            case GameObject::SPIKE:
                gameOver(dynamic_cast<Item::Spike*>(object)->CollisionPlayer(player, delta));
                break;
            case GameObject::EXIT:
                gameOver(dynamic_cast<Item::Exit*>(object)->CollisionPlayer(player, delta));
                break;
        }
    }
}

void GameController::GameController::checkCollisionBetweenObjects() {
    sf::Vector2u playerSize = player->GetSprite().getTexture()->getSize();
    std::pair<int, int> tileSize = map.GetTileSize();
    std::vector<sf::Sprite> tiles = map.GetTilesFromLayer("platform");

    for (auto& object: gameObjects){
        if (object->type != GameObject::BOX) continue;

        auto object_pos = object->GetCoordinates();
        for(auto& tile : tiles) {
            if(object->GetSprite().getGlobalBounds().intersects(tile.getGlobalBounds())) {
                if (object->GetSprite().getPosition().x < tile.getPosition().x) {
                    object->SetCoordinates(sf::Vector2f(tile.getPosition().x - tileSize.second, object_pos.y));
                } else {
                    object->SetCoordinates(sf::Vector2f(tile.getPosition().x + tileSize.second, object_pos.y));
                }
            }
        }
//        for (auto& object2: gameObjects){
//
//        }
    }


}

void GameController::GameController::gameOver(int status) {
    if (status == 0) return;
    gameStatus = status;
}
