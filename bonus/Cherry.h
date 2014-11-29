#pragma once

#include <../OpenGLHeaders.h>

#include "Bonus.h"

class Cherry : public Bonus {

    float gameTime;

    public:
        void update(float ticks, float gameTime);
        void render();
        
};
