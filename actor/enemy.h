#pragma once

#include <GL/glut.h> // Header File For The GLUT Library 
#include <GL/gl.h>	 // Header File For The OpenGL32 Library
#include <GL/glu.h>	 // Header File For The GLu32 Library

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include "../direction.h"
#include "../tile.h"

#include "actor.h"
#include "player.h"

class Enemy : public Actor {

    protected:
        DIRECTION direction;
        bool scatter;
        Player * player;
        Tile * currentTile;
        float position;
        float totalTicks;

        void setRandomDirection();
        virtual void resolvePosition(float movement);
        virtual pos getTargetPosition();
        virtual void setColor();
        pos targetPosition;
        
    public:
        virtual ~Enemy() {};
        
        void start();
        void render(float ticks);
        DIRECTION getDirection();
        point getPosition();
        void setCurrentTile(Tile * tile);
        Tile * getCurrentTile();        
        void setPlayer(Player * player);
        void setScatter(bool scatter);
};
