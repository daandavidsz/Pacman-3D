#pragma once

#include <GL/glut.h> // Header File For The GLUT Library 
#include <GL/gl.h>	 // Header File For The OpenGL32 Library
#include <GL/glu.h>	 // Header File For The GLu32 Library

#include <iostream>
#include <math.h>
#include <stdio.h> 
#include <algorithm>
#include <vector>
#include <map>

#include "../Direction.h"
#include "Vector.h"
#include "Particle.h"
#include "BloodParticle.h"

class PacmanExplosion {

    private:
        float totalTicks;
        std::map<int, Particle> particles;
        std::vector<BloodParticle> bloodParticles;
        Vector normalizeVector(Vector vector);
    
    public:
        PacmanExplosion();
        void reset();
        void render(float ticks);
        bool completed();

};
