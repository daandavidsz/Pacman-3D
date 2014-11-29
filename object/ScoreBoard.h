#pragma once

#include <OpenGLHeaders.h>

#include <stdlib.h> 
#include <iostream> 
#include <string> 
#include <sstream>
#include <map>
#include <bitset>
#include <stack>

#include "../EventObserver.h"
#include "../EventSystem.h"

class ScoreBoard : public EventObserver {

    private:
        unsigned int score;
        int ghostPoints;
        float lastTicks;
        std::vector< std::bitset<15> > digits;
        std::stack<int> numberStack;
        float glow[10][15];

    public:
    
        void reset();
        virtual void onSignal(std::string name);    
        void update(float ticks);
        void render();
        ScoreBoard();

};
