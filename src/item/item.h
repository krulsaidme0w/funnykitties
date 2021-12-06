#pragma once

#include "gameobject.h"

namespace Item{
    class Spring: public GameObject::GameObject{
    public:
        Spring(sf::Sprite sprite) : GameObject::GameObject(sprite){}
    };

}