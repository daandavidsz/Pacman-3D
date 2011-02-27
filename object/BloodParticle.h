#pragma once

#include <GL/glut.h> // Header File For The GLUT Library 
#include <GL/gl.h>	 // Header File For The OpenGL32 Library
#include <GL/glu.h>	 // Header File For The GLu32 Library

#include <math.h>
#include <stdio.h> 

#include "Vector.h"

class BloodParticle {

    Vector position;   
    Vector movementVector; 
    float size;
    float splatterDirection;
    bool fallen;
    int splatters;
    int seed;
    
    public:
        BloodParticle();
        void setPosition(Vector position);
        void setMovementVector(Vector movementVector);        
        void update(float ticks);
        void render();
};
