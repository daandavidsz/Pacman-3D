#pragma once

#include <GL/glut.h> // Header File For The GLUT Library 
#include <GL/gl.h>	 // Header File For The OpenGL32 Library
#include <GL/glu.h>	 // Header File For The GLu32 Library

#include <stdio.h> 
#include <math.h> 
#include <map>
#include <vector>

#include "../Direction.h"

class PlayerView {

    private:
        point normalizeVector(point vector);
        double radius;
        double rotation;
                
    public:
        void setRotation(double rotation);
        void setRadius(double radius);
        void render(float direction, float opening, bool draw);

};
