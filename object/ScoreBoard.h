#pragma once

#include <GL/glut.h> // Header File For The GLUT Library 
#include <GL/gl.h>	 // Header File For The OpenGL32 Library
#include <GL/glu.h>	 // Header File For The GLu32 Library

#include <vector>
#include <bitset>

#include "../EventHandler.h"

class ScoreBoard : public EventHandler {

    private:
        int score;
        std::vector<std::bitset<15> > digits;
        float glow[15];

    public:
    
        virtual void onSignal(std::string name);    
        void render(float ticks);
        ScoreBoard();

};
