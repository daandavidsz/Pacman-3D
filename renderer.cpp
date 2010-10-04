#include <iostream>
#include <ctime>
#include <math.h>
#include <vector>

#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

#include "direction.h"
#include "timer.cpp"
#include "game.h"

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
        	
            //GLfloat ambient[] = { 1.0f, 1.0f, 1.0f };
            //glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
            //GLfloat specular[] = {1.0f, 1.0f, 1.0f , 1.0f};
            //glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

            Renderer::handleLighting(true);

    	    //glEnable(GL_CULL_FACE);
        	
            glEnable (GL_BLEND);
            glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        	    
            glClearDepth(1.0);				        // Enables Clearing Of The Depth Buffer
            glDepthFunc(GL_LESS);			        // The Type Of Depth Test To Do
            glEnable(GL_DEPTH_TEST);		        // Enables Depth Testing
            glShadeModel(GL_SMOOTH);			    // Enables Smooth Color Shading
            
            //glMatrixMode(GL_PROJECTION);
            glLoadIdentity(); // Reset The Projection Matrix

            gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f); // Calculate The Aspect Ratio Of The Window

            glMatrixMode(GL_MODELVIEW);
        };
        
        static void handleLighting(bool active) {
            if (!active) return;
        }

        static void reSizeGLScene(int width, int height)
        {
            if (height==0) // Prevent A Divide By Zero If The Window Is Too Small
            height=1;

            glViewport(0, 0, width, height); // Reset The Current Viewport And Perspective Transformation

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();

            gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
            glMatrixMode(GL_MODELVIEW);
        };
    
        static void createCircle(int k, int r, int h) {
            CIRCLE circle;    
            glBegin(GL_LINES);
            for (int i = 0; i < 180; i++)
            {
                circle.x = r * cos(i) - h;
                circle.y = r * sin(i) + k;
                glVertex3f(circle.x + k,circle.y - h,0);
                
                circle.x = r * cos(i + 0.1) - h;
                circle.y = r * sin(i + 0.1) + k;
                glVertex3f(circle.x + k,circle.y - h,0);
            }
            glEnd();
        }

        static void createPlayer()
        {
            glLoadIdentity();
            glTranslatef(xshift, yshift, -20.0);
            glColor3f (1.0, 0.0, 0.0);
            createCircle(1, 1, 1);
        };
        
        /* The main drawing function. */
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

            // Framerate limiter
            /*
            if (fps > 0) {
                float beAt = 1.0 / MAXFPS * fps;
                float nowAt = now - (int)now;
                float diff = beAt - nowAt;                
                if (diff > 0.0) {
                    int m = 1000000;
                    usleep(diff * m);
                }
            }
            */
            
            bool paused = game.isPaused();
            if (paused) {
                sleep(1);
                lastClock = timer.getSeconds();
                return;
            }
            lastClock = now;
            
            float movement = (float)ticks * 5;
            
            switch (direction) {
                case up:
                    yshift += movement; break;
                case down:
                    yshift -= movement; break;
                case left:
                    xshift += movement; break;
                case right:
                    xshift -= movement; break;
                case none:
                    break;
            }

            glLoadIdentity();
            game.render(ticks);
            /*
            glTranslatef(0.0, 0.0, 0.04);
            
            glLoadIdentity();
            glTranslatef(0.4, 0.3, -1.0); 

            glPushMatrix();
                glScalef(0.0003, 0.0003, 0.0003);   
                glEnable(GL_LINE_SMOOTH);
                glColor3f (0.0, 1.0, 0.0);
                char fpsString[10];
                sprintf(fpsString, "%d", lastFps);
                for (char *c = fpsString; *c; c++) {
                    glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, *c);
                }
            glPopMatrix();
            */

            // swap the buffers to display, since double buffering is used.
            glutSwapBuffers();
        };

        /* The function called whenever a key is pressed. */
        static void keyPressed(unsigned char key, int /*x*/, int /*y*/) 
        {
            game.handleKeystroke(key);
            if (key == ESCAPE) 
            { 
              /* shut down our window */
              glutDestroyWindow(window); 
              /* exit the program...normal termination. */
              exit(0);                   
            }
        };

        static void specialKey(int key, int x, int y) {
            game.handleSpecialKeystoke(key);
        }
};

Timer Renderer::timer;
float Renderer::lastClock;
