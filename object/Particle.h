#pragma once

#include <GL/glut.h> // Header File For The GLUT Library 
#include <GL/gl.h>	 // Header File For The OpenGL32 Library
#include <GL/glu.h>	 // Header File For The GLu32 Library

#include <vector>
#include <math.h>

#include "Vector.h"

class Particle {

    std::vector<Vector> qPoints;
    std::vector<Vector> qNormals;
    
    std::vector<Vector> tPoints;
    std::vector<Vector> tNormals;    
            
    Vector position;   
    Vector movementVector;       
    float totalTicks; 
    
    public:
        Particle();
        void addQuadPoint(Vector point, Vector normal);
        void addTrianglePoint(Vector point, Vector normal);        
        void setPosition(Vector position);
        void update(float ticks);
        void render();
        
        Vector getPosition();
        Vector getMovementVector();
    
};
