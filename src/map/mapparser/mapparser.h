#pragma once

#include "map.h"
#include "string"

namespace Map {
    class MapParser {
    public:
        MapParser() = default;
        ~MapParser() = default;
        Map GetMap(const std::string& path);
    };
}