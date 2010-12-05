#pragma once

enum DIRECTION {
    none,
    up,
    down,
    right,
    left
};

struct point {
    public:
        float x;
        float y;
        float z;
    
    point() {
    
    }
    
    point(float _x, float _y, float _z = 0.0) {
        int divisor = 64;
        x = floor(divisor*_x+0.5)/divisor;
        y = floor(divisor*_y+0.5)/divisor;
        z = floor(divisor*_z+0.5)/divisor;
    }
};

struct pos {
   int x;
   int y;
};
