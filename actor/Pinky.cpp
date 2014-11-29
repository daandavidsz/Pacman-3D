#include "Pinky.h"

pos Pinky::getTargetPosition() {
    if (state == SCATTER) {
        pos p;
        p.x = 28;
        p.y = 32;
        return p;
    }
    if (state == CHASE) {
        pos position = player->getCurrentTile()->getPosition();
        switch (player->getDirection()) {
            case up:
                position.y += 4; break;
            case down:
                position.y -= 4; break;        
            case left:
                position.x -= 4; break;        
            case right:
                position.x += 4; break;        
        }
        return position;
    }
    return Enemy::getTargetPosition();
}

void Pinky::setRealColor() {
    glColor3f(1, 0.0, 1);
}
