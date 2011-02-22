#pragma once

#include "Vector.h"

class Particle {

    std::vector<Vector> points;
    std::vector<Vector> normals;    
    Vector position;   
    Vector movementVector;       
    float totalTicks; 
    
    public:
        Particle();
        void addPoint(Vector point, Vector normal);
        void setPosition(Vector position);
        void update(float ticks);
        void render();
    
};
