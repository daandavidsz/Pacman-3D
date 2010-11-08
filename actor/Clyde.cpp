#include "Clyde.h"

pos Clyde::getTargetPosition() {
    if (state == SCATTER) {
        pos p;
        p.x = 0;
        p.y = 32;
        return p;
    }
    if (state == CHASE && this->distance(currentTile->getPosition(), player->getCurrentTile()->getPosition()) < 8) {
        pos p;
        p.x = 0;
        p.y = 32;
        return p;    
    }
    return Enemy::getTargetPosition();
}

void Clyde::setRealColor() {
    glColor3f(1.0, 0.5, 0.0);
}
