#pragma once

#include "../direction.h"
#include "../eventhandler.h"

class Actor : public EventHandler {

    protected:
        void resolvePosition(float movement);
        bool isOpposite(DIRECTION a, DIRECTION b);
        DIRECTION getOpposite(DIRECTION dir);
        float distance(pos a, pos b);
        
        point normalizeVector(point vector);
        
        void vectorOffset (point *pIn, point *pOffset, point *pOut);
        void vectorGetNormal (point *a, point *b, point *pOut);
        bool vectorNormalize (point *pIn, point *pOut);
        point computeFaceNormal (point *p1, point *p2, point *p3, point *pOut);
        point computeVertexNormal (point a, point b, point c, point d);
        
    public:
        void render(float ticks);
};
