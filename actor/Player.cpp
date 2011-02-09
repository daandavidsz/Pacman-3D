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

void Player::render(float ticks) {
    totalTicks += ticks;

    if (game->getState() != stopped) {
        this->resolvePosition(ticks * 8.0);
    }
    
    point center = currentTile->getCenter();
    
    switch (direction) {
        case right: center.x += position; break;
        case left: center.x -= position; break;
        case up: center.y += position; break;
        case down: center.y -= position; break;                
        default: break;        
    }

    double r = 0.7;
    int lats = 12;
    int longs = 12;

    float i, j;

    glPushMatrix();

    glTranslatef(center.x, center.y, -19.5);
    glRotatef(90,0,1,0);  
    
    switch (direction) {
        case left:
            glRotatef(90,1,0,0); break;       
        case right:
            glRotatef(270,1,0,0); break;
        case up:
            glRotatef(180,1,0,0); break;
        case down:
            glRotatef(0,1,0,0); break;
        case none:
            glRotatef(0,1,0,0); break;        
    }
    
    glRotatef(90,0,0,1);
        
    std::vector<point> points; 
    std::map<int,bool> mouth;
    
    int threshHold = 0;
    float alpha = 1.0;
    
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
        if (threshHold < -90) {
            direction = none;
            state = ALIVE;
            emit("playerdied");        
        }
        if (threshHold < 0) {
            threshHold = 0;
        }
        if (threshHold < 90) {
            pacmanExplosion.render(ticks);        
            alpha = std::max(0.0, 1.0 - (dyingProgress-0.5)*3);
        }
        dyingProgress += ticks * 1;
    }
    
    for(i = 1; i <= lats; i++) {
        double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
        double z0  = sin(lat0);
        double zr0 = cos(lat0);

        double lat1 = M_PI * (-0.5 + (double) i / lats);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);

        bool drawn = false;
        
        float m;

        for(j = 0; j <= 360; j += 360 / longs) {
            if (j <= threshHold || j >= 360 - threshHold) {
                double lng = 2 * M_PI * (double) (j - 1) / 360;
                double x = cos(lng);
                double y = sin(lng);
            
                glColor3f(1, 1, 0);

                points.push_back(point(r * x * zr1, r * y * zr1, r * z1));
                points.push_back(point(r * x * zr0, r * y * zr0, r * z0));
            }
            else if (!drawn) {
                drawn = true;
                
                m = (int)(0.5 + threshHold);
                               
                double lng = 2 * M_PI * (double) (m - 1) / 360;
                double x = cos(lng);
                double y = sin(lng);


                points.push_back(point(r * x * zr1, r * y * zr1, r * z1));
                points.push_back(point(r * x * zr0, r * y * zr0, r * z0));
                //glColor3f(1,0,0);
                mouth[(int)points.size()] = true;
                points.push_back(point(r * x * zr1, r * y * zr1, r * z1));
                points.push_back(point(r * x * zr0, r * y * zr0, r * z0));
                points.push_back(point(0, 0, r * z1));
                points.push_back(point(0, 0, r * z0));
                                
                m = (int)(0.5 + 360 - threshHold);
                
                lng = 2 * M_PI * (double) (m - 1) / 360;
                x = cos(lng);
                y = sin(lng);

                points.push_back(point(r * x * zr1, r * y * zr1, r * z1));
                points.push_back(point(r * x * zr0, r * y * zr0, r * z0));
                
                mouth[(int)points.size()] = false;
                //glColor3f(1,1,0);
                points.push_back(point(r * x * zr1, r * y * zr1, r * z1));
                points.push_back(point(r * x * zr0, r * y * zr0, r * z0));                
            }            

        }

    }
    
    glColor4f(1,1,0, alpha);
    
    bool isMouth = false;
    
    glBegin(GL_QUAD_STRIP);
    for (unsigned int i = 0; i < points.size(); i++) {
    
        if (mouth.find(i) != mouth.end()) {
            switch (mouth.find(i)->second) {
                case true:
                    glColor4f(1, 0, 0, alpha);
                    isMouth = true;
                    break;
                case false:
                    glColor4f(1, 1, 0, alpha);
                    isMouth = false;
                    break;
            }
        }
    
        point p = points[i];
        
        point n = normalizeVector(p);
        if (isMouth) {
            glNormal3f(-1, 0, 0);
        }
        else {
            glNormal3f(n.x, n.y, n.z);
        }
        
        glVertex3f(p.x, p.y, p.z);
    }
    glEnd();
    
    /*
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
    for (unsigned int i = 0; i < points.size(); i++) {
        point p = points[i];
        glVertex3f(p.x, p.y, p.z);
        glVertex3f(0.5,0.5,0.5);
    }
    glEnd();
    */
    
    glPopMatrix();
}

Tile * Player::getCurrentTile() {
    return currentTile;
}
