#include "math.h"

#include "actor.h"

bool Actor::isOpposite(DIRECTION a, DIRECTION b) {
    switch (a) {
        case left: return b == right;
        case up: return b == down;
        case down: return b == up;
        case right: return b == left;       
        default: return false;                 
    }
}

float Actor::distance(pos a, pos b) {
    float diffX = (float)a.x - (float)b.x;
    float diffY = (float)a.y - (float)b.y;    
    if (diffX < 0.0) diffX = 0.0-diffX;
    if (diffY < 0.0) diffY = 0.0-diffY;    
    
    return sqrt((diffX*diffX) + (diffY*diffY));
}

point Actor::normalizeVector(point vector) {
    point normalizedVector;
    float len = (float)(sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z));
    normalizedVector.x = vector.x / len;
    normalizedVector.y = vector.y / len;
    normalizedVector.z = vector.z / len;
    return normalizedVector;
}

// Offset pIn by pOffset into pOut
void Actor::vectorOffset (point *pIn, point *pOffset, point *pOut)
{
   pOut->x = pIn->x - pOffset->x;
   pOut->y = pIn->y - pOffset->y;
   pOut->z = pIn->z - pOffset->z;
}

// Compute the cross product a X b into pOut
void Actor::vectorGetNormal (point *a, point *b, point *pOut)
{
   pOut->x = a->y * b->z - a->z * b->y;
   pOut->y = a->z * b->x - a->x * b->z;
   pOut->z = a->x * b->y - a->y * b->x;
}

// Normalize pIn vector into pOut
bool Actor::vectorNormalize (point *pIn, point *pOut)
{
   float len = (float)(sqrt(pIn->x*pIn->x + pIn->y*pIn->y + pIn->z*pIn->z));
   if (len)
   {
      pOut->x = pIn->x / len;
      pOut->y = pIn->y / len;
      pOut->z = pIn->z / len;
      return true;
   }
   return false;
}

// Compute p1,p2,p3 face normal into pOut
point Actor::computeFaceNormal (point *p1, point *p2, point *p3)
{
    point * pOut = new point();
    // Uses p2 as a new origin for p1,p3
    point a;
    vectorOffset(p3, p2, &a);
    point b;
    vectorOffset(p1, p2, &b);
    // Compute the cross product a X b to get the face normal
    point pn;
    vectorGetNormal(&a, &b, &pn);
    // Return a normalized vector
    vectorNormalize(&pn, pOut);
    
    return *pOut;
}

point Actor::computeVertexNormal (point a, point b, point c, point d) {
    point value;
    value.x = (a.x + b.x + c.x + d.x) / 4;
    value.y = (a.y + b.y + c.y + d.y) / 4;
    value.z = (a.z + b.z + c.z + d.z) / 4;
    return normalizeVector(value);
}

