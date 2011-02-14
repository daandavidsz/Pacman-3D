#pragma once

#include <GL/glut.h> // Header File For The GLUT Library 

#include "Bonus.h"

class Cherry : public Bonus {

    float gameTime;

    public:
        void update(float ticks, float gameTime);
        void render();
        
};
