#include "Tile.h"

Tile::Tile() {
    if (rand() % 50 == 7) {
        bonus = new Cherry();
    }
}

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

void Tile::setVisited() {
    if (!visited) {
        if (energizer) {
            emit("energizer");       
        }
        visited = true;
    }
}

void Tile::setEnergizer() {
    energizer = true;
}

void Tile::render(float ticks, float gameTime) {
    float pointX = center.x - 0.5;
    float pointY = center.y - 0.5;
    
    if (visited) return;

    if (energizer) {
        glColor4f(1, 1.0/255*184, 1.0/255*151, 0.2 + 0.8*sin(M_PI * (gameTime - (int)gameTime)));
        glPushMatrix();
        glTranslatef(pointX+0.5, pointY+0.5, -19.5);
        glutSolidSphere(0.4, 12, 12);
        glPopMatrix();
    }
    else {
        glColor4f(1, 1.0/255*184, 1.0/255*151, 1);
        glPushMatrix();
        glTranslatef(pointX+0.5, pointY+0.5, -19.5);
        glutSolidSphere(0.08, 4, 4);
        glPopMatrix();
    }
    
    if (bonus != NULL) {
        point center = getCenter();    
        glPushMatrix();
        glTranslatef(center.x, center.y, -19.5);
        bonus->render(ticks, gameTime);
        glPopMatrix();
    }
}
