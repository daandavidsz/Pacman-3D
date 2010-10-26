#include "Clyde.h"

void Clyde::resolvePosition(float ticks) {
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

pos Clyde::getTargetPosition() {
    if (state == SCATTER) {
        pos p;
        p.x = 0;
        p.y = 32;
        return p;
    }
    
    if (this->distance(currentTile->getPosition(), player->getCurrentTile()->getPosition()) < 8) {
        pos p;
        p.x = 0;
        p.y = 32;
        return p;    
    }
    
    pos position = player->getCurrentTile()->getPosition();
    return position;
}

void Clyde::setRealColor() {
    glColor3f(1.0, 0.5, 0.0);
}
