#pragma once

#include "../Direction.h"
#include "../EventHandler.h"

class Bonus : public EventHandler {

    public:
        virtual void update(float ticks, float gameTime);    
        virtual void render();
};
