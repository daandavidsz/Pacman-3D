#include <OpenGLHeaders.h>
#include <unistd.h>  // needed to sleep
#include <stdlib.h>  // exit()
#include <stdio.h> 
#include <string.h>

#include <pthread.h>

#include "Renderer.cpp"

int main(int argc, char **argv) 
{  
    /* Initialize GLUT state - glut will take any command line arguments that pertain to it or 
     X Windows - look at its documentation at http://reality.sgi.com/mjk/spec3/spec3.html */  
    glutInit(&argc, argv);  
    
    /* Select type of Display mode:   
     Double buffer 
     RGBA color
     Alpha components supported 
     Depth buffered for automatic clipping */  
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  

    glutInitWindowSize(1024, 768);  
    glutInitWindowPosition(0, 0);  
    window = glutCreateWindow("Pacman");  

    /* Register the function to do all our OpenGL drawing. */
    glutDisplayFunc(&Renderer::drawGLScene);  

    /* Even if there are no events, redraw our gl scene. */
    glutIdleFunc(&Renderer::drawGLScene);

    /* Register the function called when our window is resized. */
    glutReshapeFunc(&Renderer::reSizeGLScene);

    /* Register the function called when the keyboard is pressed. */
    glutKeyboardFunc(&Renderer::keyPressed);
    glutSpecialFunc(&Renderer::specialKey);

    /* Initialize our window. */
    Renderer::initGL(1024, 768);

    /* Start Event Processing Engine */  
    glutMainLoop();  

    return 1;
}
