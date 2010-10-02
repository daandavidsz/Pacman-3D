#include "tile.h"

void Tile::setPosition(pos tilePosition) {
    position = tilePosition;
}

pos Tile::getPosition() {
    return position;
}

point Tile::getCenter() {
    return center;
}

void Tile::setCenter(point centerPoint) {
    center = centerPoint;
}

void Tile::setExit(DIRECTION dir, Tile * exit) {
    exits[(int)dir] = exit;
}

bool Tile::hasExit(DIRECTION dir) {
    return exits[(int)dir] != NULL;
}

Tile * Tile::getExit(DIRECTION dir) {
    return exits[(int)dir];
}

void Tile::setColor(int c) {
    color = c;
}

void Tile::setSmell() {
    visited = true;
}

void Tile::render(float ticks) {
    float pointX = center.x - 0.5;
    float pointY = center.y - 0.5;
    
    if (!visited) {
        glColor4f(1.0, 1.0, 0.0, 0.7);
        glBegin (GL_QUADS);
            glVertex3f(pointX+0.45, pointY+0.45, -19.5);
            glVertex3f(pointX+0.55, pointY+0.45, -19.5);
            glVertex3f(pointX+0.55, pointY+0.55, -19.5);
            glVertex3f(pointX+0.45, pointY+0.55, -19.5);
        glEnd ();
    }
}
