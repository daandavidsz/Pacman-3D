#pragma once

#define M_PI 3.14159265358979323846

#include <time.h>

#include "actor/Player.h"
#include "actor/Enemy.h"
#include "actor/Blinky.h"
#include "actor/Pinky.h"
#include "actor/Inky.h"
#include "actor/Clyde.h"
#include "object/ScoreBoard.h"
#include "view/PlayerView.h"
#include "Direction.h"
#include "Maze.h"
#include "EventObserver.h"
#include "EventSystem.h"

class Game : public EventObserver {

    private:
        PlayerView playerView;
        Maze maze;
        ScoreBoard scoreBoard;    
        Player player;
        
        Pinky pinky;
        Blinky blinky;
        Inky inky;
        Clyde clyde;  
        std::vector<Enemy*> enemies;

        char lives;
        float gameTime;
        bool paused;
        GAMESTATE gameState;
        void handleLighting();
    
    public:
        virtual void onSignal(std::string name);    
        void load();
        void reset();
        Maze getMaze();
        void update(float ticks);
        void render();
        void handleKeystroke(unsigned char key);
        void handleSpecialKeystoke(int key);
        bool isPaused();
        GAMESTATE getState();
};
