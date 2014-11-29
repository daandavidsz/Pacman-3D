#include "Renderer.h"

void Renderer::initGL(int width, int height) {
    game.load();

    glClearColor(0.0, 0.0, 0.0, 0.5);
	
    glEnable(GL_CULL_FACE);
    
    //glPolygonMode(GL_FRONT, GL_LINE); 
	
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	    
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    
    glLoadIdentity();

    gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f); // Calculate the aspect ratio of the window

    glMatrixMode(GL_MODELVIEW);
};
        
void Renderer::reSizeGLScene(int width, int height) {
    if (height == 0) height = 1;// Prevent a divide by zero if the window is too small

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
    glMatrixMode(GL_MODELVIEW);
};
        
// The main drawing function
void Renderer::drawGLScene() {
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
    game.update(ticks);
    game.render();

    // Swap the buffers to display, since double buffering is used.
    glutSwapBuffers();
};

// The function called whenever a key is pressed
void Renderer::keyPressed(unsigned char key, int x, int y) 
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

void Renderer::specialKey(int key, int x, int y) {
    game.handleSpecialKeystoke(key);
}
