#pragma once

#include <OpenGLHeaders.h>

#include <iostream>
#include <math.h>
#include <stdio.h> 

#include "bonus/Cherry.h"
#include "Direction.h"
#include "EventSystem.h"

class Tile {

    Tile * exits[10];
    Bonus * bonus;
    pos position;
    point center;
    int color;
    int steps;
    float smell;
    float gameTime;
    float lastTicks;
    
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
        void update(float ticks, float gameTime);
        void render();
        void setPosition(pos position);
        pos getPosition();
};
