#include "Inky.h"

pos Inky::getTargetPosition() {
    if (state == SCATTER) {
        pos p;
        p.x = 28;
        p.y = 0;
        return p;
    }
    if (state == CHASE) {
        pos position = player->getCurrentTile()->getPosition();
        pos blinkyPos = blinky->getCurrentTile()->getPosition();

        switch (player->getDirection()) {
            case up:
                position.y += 2; break;
            case down:
                position.y -= 2; break;        
            case left:
                position.x -= 2; break;        
            case right:
                position.x += 2; break;    
        }
            
        pos newPos;
        
        newPos.x = position.x - (2 * (blinkyPos.x - position.x));
        newPos.y = position.y - (2 * (blinkyPos.y - position.y));    
        
        return newPos;
    }
    return Enemy::getTargetPosition();
}

void Inky::setRealColor() {
    glColor3f(0.0, 0.9, 1);
}

void Inky::setBlinky(Blinky * b) {
    blinky = b;
}
