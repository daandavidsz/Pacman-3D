#pragma once

struct Vector
{
     float x,y,z;
     
     Vector() {
        x = 0.0;
        y = 0.0;
        z = 0.0;
     }
     
     Vector(float _x, float _y, float _z) {
        x = _x;
        y = _y;
        z = _z;                
     }

     Vector operator+(const Vector &other)
     {
          Vector result;
          result.x = x + other.x;
          result.y = y + other.y;
          result.z = z + other.z;
          return result;
     }

     Vector operator*(float scalar)
     {
          Vector result;
          result.x = x * scalar;
          result.y = y * scalar;
          result.z = z * scalar;
          return result;
     }
};
