#pragma once

#include <GL/glut.h> // Header File For The GLUT Library 
#include <GL/gl.h>	 // Header File For The OpenGL32 Library
#include <GL/glu.h>	 // Header File For The GLu32 Library

#include <stdlib.h> 
#include <iostream> 
#include <string> 
#include <sstream>
#include <map>
#include <bitset>
#include <stack>

#include "../EventObserver.h"

class ScoreBoard : public EventObserver {

    private:
        unsigned int score;
        int ghostPoints;
        float lastTicks;
        std::vector< std::bitset<15> > digits;
        std::stack<int> numberStack;
        float glow[10][15];

    public:
    
        virtual void onSignal(std::string name);    
        void update(float ticks);
        void render();
        ScoreBoard();

};
