#pragma once

#include <GL/glut.h> // Header File For The GLUT Library 
#include <GL/gl.h>	 // Header File For The OpenGL32 Library
#include <GL/glu.h>	 // Header File For The GLu32 Library

#include <iostream>
#include <math.h>
#include <stdio.h> 

#include "bonus/Cherry.h"
#include "Direction.h"
#include "EventHandler.h"

class Tile : public EventHandler {

    Tile * exits[10];
    Bonus * bonus;
    pos position;
    point center;
    int color;
    int steps;
    float smell;
    
    bool energizer;
    bool visited;

    public:
        Tile();
        
        void setCenter(point centerPoint);
        point getCenter();        
        void setExit(DIRECTION direction, Tile * tile);
        bool hasExit(DIRECTION direction);
        Tile * getExit(DIRECTION direction);
        void setColor(int color);
        void setVisited();
        void setEnergizer();
        void render(float ticks, float gameTime);        
        void setPosition(pos position);
        pos getPosition();
};
