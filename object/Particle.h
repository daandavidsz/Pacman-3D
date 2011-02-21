#pragma once

#include "Vector.h"

class Particle {

    std::vector<Vector> points;
    Vector position;   
    Vector movementVector;       
    float totalTicks; 
    
    public:
        Particle();
        void addPoint(Vector point);
        void setPosition(Vector position);
        void update(float ticks);
        void render();
    
};
