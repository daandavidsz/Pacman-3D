#pragma once

#include <GL/glut.h> // Header File For The GLUT Library 

#include "Bonus.h"

class Cherry : public Bonus {

    public:
        void render(float ticks, float gameTime);
        
};
