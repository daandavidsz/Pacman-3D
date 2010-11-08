#include "Blinky.h"

pos Blinky::getTargetPosition() {
    if (state == SCATTER) {
        pos p;
        p.x = 0;
        p.y = 0;
        return p;
    }
    return Enemy::getTargetPosition();
}

void Blinky::setRealColor() {
    glColor3f(1, 0, 0);
}
