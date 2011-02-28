#pragma once

#include <GL/glut.h> // Header File For The GLUT Library 
#include <GL/gl.h>	 // Header File For The OpenGL32 Library
#include <GL/glu.h>	 // Header File For The GLu32 Library

#include <stdio.h> 
#include <math.h> 
#include <map>

class PlayerView {

    public:
        void render(float direction, float opening);

};
