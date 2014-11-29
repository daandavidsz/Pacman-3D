#pragma once

#include <iostream>
#include <math.h>
#include <vector>

#include <stdio.h>
#include <unistd.h>

#include "Direction.h"
#include "Timer.cpp"
#include "Game.h"

/* ascii codes */
#define ESCAPE 27

enum DIRECTION direction = none;

/* The number of our GLUT window */
int window; 

float xshift = 0.0f;
float yshift = 0.0f;
int fps = 0;
int lastFps = 0;

const int MAXFPS = 50;            
Game game;
        
typedef struct
{
    float x;
    float y;
} CIRCLE;

class Renderer {
    
    public:
        static int x;
        static Timer timer;

        static float lastClock;
        
        static void initGL(int width, int height);
        static void reSizeGLScene(int width, int height);
        static void drawGLScene();
        static void keyPressed(unsigned char key, int x, int y);
        static void specialKey(int key, int x, int y);
};

Timer Renderer::timer;
float Renderer::lastClock;
