#pragma once

#include <GL/glut.h> // Header File For The GLUT Library 
#include <GL/gl.h>	 // Header File For The OpenGL32 Library
#include <GL/glu.h>	 // Header File For The GLu32 Library

#include <iostream>
#include <math.h>
#include <stdio.h> 
#include <algorithm>
#include <vector>

#include "../Direction.h"

class PacmanExplosionParticle {

    public:
        float totalTicks, xShift, yShift, zShift;
        PacmanExplosionParticle();
        void render(float totalTicks);

};

class PacmanExplosion {

    private:
        float totalTicks;
        std::vector<PacmanExplosionParticle> particles;
        point normalizeVector(point vector);
    
    public:
        PacmanExplosion();
        void reset();
        void render(float ticks);
        bool completed();

};
