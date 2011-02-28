#include "Player.h"
#include "../Game.h"

DIRECTION Player::getDirection() {
    return direction;
}

void Player::setDirection(DIRECTION dir) {
    direction = dir;
}

DIRECTION Player::getWantedDirection() {
    return wantedDirection;
}

void Player::setWantedDirection(DIRECTION dir) {
    wantedDirection = dir;
}

void Player::updateDirection() {
    direction = wantedDirection;
}

void Player::setCurrentTile(Tile * tile) {
    currentTile = tile;
}

PLAYERSTATE Player::getState() {
    return state;
}

void Player::setDying() {
    if (state != DYING) {
        state = DYING;
        dyingProgress = 0;
        pacmanExplosion.reset();   
    }
}

void Player::resolvePosition(float movement) {

    // Backwardo
    if (this->isOpposite(direction, wantedDirection)) {
        currentTile = currentTile->getExit(direction);
        position = 1.0-position;
        direction = wantedDirection;
    }

    if (direction != none) position += movement;
    if (direction != none && position < 1.0) return;
    
    if (direction == none && currentTile->hasExit(wantedDirection)) {
        direction = wantedDirection;
        currentTile->getExit(direction)->setColor(1);        
        wantedDirection = none;
    }
    
    if (position >= 1.0) {
        currentTile = currentTile->getExit(direction);
        currentTile->setVisited();            
        if (currentTile->hasExit(wantedDirection)) {
            position -= 1.0;
            direction = wantedDirection;
            wantedDirection = none;
            return;
        }
        position = 0.0;
        if (!currentTile->hasExit(direction)) {
            direction = none;
        }
    }
}

point Player::getPosition() {
    point currentPos = currentTile->getCenter(); 
    switch (direction) {
        case right: currentPos.x += position; break;
        case left: currentPos.x -= position; break;
        case up: currentPos.y += position; break;
        case down: currentPos.y -= position; break;  
        default: break;              
    }
    return currentPos;
}

void Player::update(float ticks) {
    lastTicks = ticks;
    totalTicks += ticks;
    if (game->getState() != stopped) {
        this->resolvePosition(lastTicks * 8.0);
    }    
}

void Player::render() {
    point currentPos = getPosition();
    
    glPushMatrix();

    glTranslatef(currentPos.x, currentPos.y, -19.5);
    
    float drawDirection = 0;
    switch (direction) {
        case left:
            drawDirection = 90; break;    
        case right:
            drawDirection = 270; break;
        case up:
            drawDirection = 180; break;
        case down:
            drawDirection = 0; break;
        case none:
            drawDirection = 0; break;        
    }
    
    float threshHold = 0;
    
    if (state == ALIVE) {
        threshHold = (int)(position * 90 + 45) % 90;
        if (threshHold > 45) { 
            threshHold = 90 + threshHold;
        }
        else {
            threshHold = 180 - threshHold;
        }
    }
    else if (state == DYING) {
        threshHold = 180 - (int)(dyingProgress * 180);
        if (threshHold < -320) {
            direction = none;
            state = ALIVE;
            EventSystem::getInstance()->emit("playerdied");        
        }
        dyingProgress += lastTicks * 1;
    }
    
    if (direction == none) {
        playerView.render(drawDirection, 180-25, state == ALIVE);
    }
    else {
        playerView.render(drawDirection, threshHold, state == ALIVE);
    }
    
    if (state == DYING) {
        pacmanExplosion.render(lastTicks);
    }
    
    glPopMatrix();
}

Tile * Player::getCurrentTile() {
    return currentTile;
}
