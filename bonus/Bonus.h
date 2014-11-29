#pragma once

#include "../Direction.h"
#include "../EventObserver.h"

class Bonus : public EventObserver {

    public:
        virtual void update(float ticks, float gameTime);    
        virtual void render();
};
