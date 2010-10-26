#include "inky.h"

void Inky::resolvePosition(float ticks) {
    std::vector<DIRECTION> directions;
    DIRECTION dirs[] = {up, down, left, right};
    DIRECTION dir = none;

    targetPosition = this->getTargetPosition();

    int distance = 99;
    for (int i = 0; i < 4; i++) {
        if (currentTile->hasExit(dirs[i])) {
            float thisDistance = this->distance(currentTile->getExit(dirs[i])->getPosition(), targetPosition);
            if (!this->isOpposite(dirs[i], direction)) directions.push_back(dirs[i]);
            if (thisDistance < distance && !this->isOpposite(dirs[i], direction)) {
                dir = dirs[i];
                distance = thisDistance;
            }
        }
    }

    direction = dir;    
}

pos Inky::getTargetPosition() {
    if (state == SCATTER) {
        pos p;
        p.x = 28;
        p.y = 0;
        return p;
    }
    
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

void Inky::setRealColor() {
    glColor3f(0.0, 0.9, 1);
}

void Inky::setBlinky(Blinky * b) {
    blinky = b;
}
