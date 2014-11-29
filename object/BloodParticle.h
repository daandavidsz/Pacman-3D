#pragma once

#include <OpenGLHeaders.h>

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
