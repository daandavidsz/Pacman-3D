#pragma once

#define M_PI 3.14159265358979323846

#include <GL/glut.h> // Header File For The GLUT Library 
#include <GL/gl.h>	 // Header File For The OpenGL32 Library
#include <GL/glu.h>	 // Header File For The GLu32 Library

#include <stdio.h> 
#include <math.h> 

#include "../direction.h"
#include "../tile.h"

#include "actor.h"

class Player : Actor {

    private:
        DIRECTION direction;
        DIRECTION wantedDirection;        
        
        Tile * currentTile;
        float position;
        
        void resolvePosition(float movement);
        
    public:
    
        DIRECTION getDirection();
        void setDirection(DIRECTION direction);
        DIRECTION getWantedDirection();
        void setWantedDirection(DIRECTION direction);
        void updateDirection();
        void render(float ticks);
        
        point getPosition();
        void incrPosition(float number);        

        void setCurrentTile(Tile * tile);
        Tile * getCurrentTile();
};
