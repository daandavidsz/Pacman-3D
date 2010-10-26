#pragma once

#define M_PI 3.14159265358979323846

#include <time.h>

#include "actor/player.h"
#include "actor/enemy.h"
#include "actor/blinky.h"
#include "actor/pinky.h"
#include "actor/inky.h"
#include "actor/clyde.h"
#include "maze.h"
#include "eventhandler.h"

class Game : public EventHandler {

    Maze maze;
    Player player;

    Pinky pinky;
    Blinky blinky;
    Inky inky;
    Clyde clyde;  
    std::vector<Enemy*> enemies;

    int counter;
    float gameTime;
    bool paused;
    
    protected:
        
        void handleLighting();
    
    public:
        
        virtual void onSignal(std::string name);    
        void load();
        Maze getMaze();
        void render(float ticks);
        void handleKeystroke(unsigned char key);
        void handleSpecialKeystoke(int key);
        bool isPaused();
};
