#pragma once

#include "statefull.hpp"

class Core final {
public:
    static void Initialize() {
        Statefull::Initialize();
    }
};
