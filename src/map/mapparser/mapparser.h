#pragma once

#include "map.h"
#include "string"
#include "item.h"

namespace Map {
    class MapParser {
    public:
        MapParser() = default;
        ~MapParser() = default;
        Map GetMap(const std::string& path);
        std::vector<GameObject::GameObject*> GetObjects(Map &map);
    };
}