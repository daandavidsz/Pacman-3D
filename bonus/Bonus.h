#pragma once

#include "../Direction.h"
#include "../EventHandler.h"

class Bonus : public EventHandler {

    public:
        void render(float ticks);
};
