#pragma once

#include <GL/glut.h> // Header File For The GLUT Library 
#include <GL/gl.h>	 // Header File For The OpenGL32 Library
#include <GL/glu.h>	 // Header File For The GLu32 Library

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include "../Direction.h"
#include "../Tile.h"

#include "Actor.h"
#include "Player.h"

enum ENEMYSTATE {
    CHASE,
    SCATTER,
    SCARED,
    EATEN
};

class Enemy : public Actor {

    protected:
        ENEMYSTATE state;
        DIRECTION direction;
        Player * player;
        Tile * currentTile;
        float position;
        float totalTicks;
        float gameTime;
        float scaredTime;

        void reverseDirection();
        void setRandomDirection();
        virtual void resolvePosition(float movement);
        virtual void resolveScaredPosition(float movement);        
        virtual pos getTargetPosition();
        virtual void setColor();
        virtual void setRealColor();
        pos targetPosition;
        void renderBody();
        void renderEyes();        
        
    public:
        virtual ~Enemy() {};

        void onSignal(std::string name);   
        void start();
        void render(float ticks);
        DIRECTION getDirection();
        point getPosition();
        void setCurrentTile(Tile * tile);
        Tile * getCurrentTile();        
        void setPlayer(Player * player);
};
