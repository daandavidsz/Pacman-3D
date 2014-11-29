#pragma once

#include <OpenGLHeaders.h>

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
