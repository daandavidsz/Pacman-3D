#include "pinky.h"

void Pinky::resolvePosition(float ticks) {
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

pos Pinky::getTargetPosition() {
    if (scatter) {
        pos p;
        p.x = 28;
        p.y = 32;
        return p;
    }
    
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

void Pinky::setColor() {
    glColor3f(1, 0.0, 1);
}
