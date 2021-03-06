#pragma once

#define M_PI 3.14159265358979323846

#include <OpenGLHeaders.h>

#include <stdio.h> 
#include <math.h> 
#include <map>

#include "../EventSystem.h"
#include "../Direction.h"
#include "../Tile.h"
#include "../object/PacmanExplosion.h"
#include "../view/PlayerView.h"

#include "Actor.h"

enum PLAYERSTATE {
    ALIVE,
    DYING,
    DEAD
};

class Player : public Actor {

    private:
        DIRECTION direction;
        DIRECTION wantedDirection;   
        PLAYERSTATE state; 
        PacmanExplosion pacmanExplosion;    
        
        float dyingProgress;
        float totalTicks;
        
        Tile * currentTile;
        float position;
        
        float lastTicks;
        
        void resolvePosition(float movement);
        
        PlayerView playerView;
        
    public:
        PLAYERSTATE getState();
        void setDying();        
        
        DIRECTION getDirection();
        void setDirection(DIRECTION direction);
        DIRECTION getWantedDirection();
        void setWantedDirection(DIRECTION direction);
        void updateDirection();
        void update(float ticks);
        void render();
        
        point getPosition();
        void incrPosition(float number);        

        void setCurrentTile(Tile * tile);
        Tile * getCurrentTile();
};
