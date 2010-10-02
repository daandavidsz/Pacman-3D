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

class Game {

    Maze maze;
    Player player;

    Pinky pinky;
    Blinky blinky;
    Inky inky;
    Clyde clyde;    

    int counter;
    float gameTime;
    
    public:
        
        void load();
        Maze getMaze();
        void render(float ticks);
        void handleKeystroke(unsigned char key);
        void handleSpecialKeystoke(int key);
};
