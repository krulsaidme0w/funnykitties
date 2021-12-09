#pragma once

#include "gameobject.h"
#include "gamecontroller.h"
#include "player.h"
#include "SFML/Graphics.hpp"

namespace Item{

    class Spring: public GameObject::GameObject{
    public:
        Spring(sf::Sprite &sprite) : GameObject::GameObject(sprite, ::GameObject::ObjectType::SPRING) {};

        //static void Init(Player::Player* p);
        void CollisionPlayer(Player::Player* player, sf::Vector2f delta);

        //static Player::Player* player;
    };

    class Box: public GameObject::GameObject{
    public:
        Box(sf::Sprite &sprite) : GameObject::GameObject(sprite, ::GameObject::ObjectType::BOX){};

        //static void Init(Player::Player* p);
        void CollisionPlayer(Player::Player* player, sf::Vector2f delta);

        //static Player::Player* player;
    };

    class Key: public GameObject::GameObject{
    public:
        Key(sf::Sprite &sprite) : GameObject::GameObject(sprite, ::GameObject::ObjectType::KEY){};

        void CollisionPlayer(Player::Player* player, sf::Vector2f delta);
    };

    class Exit: public GameObject::GameObject{
    public:
        Exit(sf::Sprite &sprite) : GameObject::GameObject(sprite, ::GameObject::ObjectType::EXIT){};

        //static void Init(Player::Player* p);
        void CollisionPlayer(Player::Player* player, sf::Vector2f delta);
        //static Player::Player* player;
    };




}