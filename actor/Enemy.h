#pragma once

#include <OpenGLHeaders.h>

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
        
        ENEMYSTATE getState();
        void onSignal(std::string name);   
        void start();
        void update(float ticks);
        void render();
        DIRECTION getDirection();
        point getPosition();
        void setCurrentTile(Tile * tile);
        Tile * getCurrentTile();        
        void setPlayer(Player * player);
};
