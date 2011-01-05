#pragma once

#include "../Direction.h"
#include "../EventHandler.h"

class Bonus : public EventHandler {

    public:
        virtual void render(float ticks, float gameTime);
};
