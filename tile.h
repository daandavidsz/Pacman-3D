#pragma once

#include <GL/glut.h> // Header File For The GLUT Library 
#include <GL/gl.h>	 // Header File For The OpenGL32 Library
#include <GL/glu.h>	 // Header File For The GLu32 Library

#include <stdio.h> 

#include "direction.h"

class Tile {

    Tile * exits[10];
    pos position;
    point center;
    int color;
    int steps;
    float smell;
    bool visited;
    
    public:
        void setCenter(point centerPoint);
        point getCenter();        
        void setExit(DIRECTION direction, Tile * tile);
        bool hasExit(DIRECTION direction);
        Tile * getExit(DIRECTION direction);
        void setColor(int color);
        void setSmell();
        void render(float ticks);        
        void setPosition(pos position);
        pos getPosition();
            
};
