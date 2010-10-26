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
        x = _x;
        y = _y;
        z = _z;
    }
};

struct pos {
   int x;
   int y;
};
