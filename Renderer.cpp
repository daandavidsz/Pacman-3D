#include <iostream>
#include <ctime>
#include <math.h>
#include <vector>

#include <sys/time.h>
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
        
        static void initGL(int width, int height) {
            game.load();
        
            glClearColor(0.0, 0.0, 0.0, 0.5);
        	
        	// Disabled for now
    	    // glEnable(GL_CULL_FACE);
        	
            glEnable (GL_BLEND);
            glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        	    
            glClearDepth(1.0);
            glDepthFunc(GL_LESS);
            glEnable(GL_DEPTH_TEST);
            glShadeModel(GL_SMOOTH);
            
            glLoadIdentity();

            gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f); // Calculate the aspect ratio of the window

            glMatrixMode(GL_MODELVIEW);
        };
        
        static void reSizeGLScene(int width, int height)
        {
            if (height == 0) // Prevent a divide by zero if the window is too small
            height = 1;

            glViewport(0, 0, width, height);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();

            gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
            glMatrixMode(GL_MODELVIEW);
        };
        
        // The main drawing function
        static void drawGLScene()
        {
            fps++;
            
            float now = timer.getSeconds();
            float ticks = now - lastClock;
            
            if (int(lastClock) != int(now)) {
                lastFps = fps;
                std::cout << "FPS: " << fps << "\n";
                std::cout << "--------\n";                
                fps = 0;
            }

            bool paused = game.isPaused();
            if (paused) {
                sleep(1);
                lastClock = timer.getSeconds();
                return;
            }
            lastClock = now;
            
            glLoadIdentity();
            game.render(ticks);

            // Swap the buffers to display, since double buffering is used.
            glutSwapBuffers();
        };

        // The function called whenever a key is pressed
        static void keyPressed(unsigned char key, int x, int y) 
        {
            game.handleKeystroke(key);
            if (key == ESCAPE || key == 'q') 
            { 
              // Shut down our window 
              glutDestroyWindow(window); 
              // Exit the program, normal termination
              exit(0);                   
            }
        };

        static void specialKey(int key, int x, int y) {
            game.handleSpecialKeystoke(key);
        }
};

Timer Renderer::timer;
float Renderer::lastClock;
