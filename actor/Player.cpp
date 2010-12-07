#include "Player.h"

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
    this->resolvePosition(ticks * 8.0);
    
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
        
    std::vector<point> points; 
        
    int threshHold = (int)(position * 180 + 90) % 180;
    if (threshHold > 90) threshHold = 180 - threshHold;
    
    for(i = 1; i <= lats; i++) {
        double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
        double z0  = sin(lat0);
        double zr0 = cos(lat0);

        double lat1 = M_PI * (-0.5 + (double) i / lats);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);

        bool drawn = false;
        
        float halfThreshHold = threshHold / 2;
        float m;

        for(j = 0; j <= 360; j += 360 / longs) {
            if (j <= 180 + 45 + halfThreshHold || j >= 360 - 45 - halfThreshHold ) {
                double lng = 2 * M_PI * (double) (j - 1) / 360;
                double x = cos(lng);
                double y = sin(lng);
            
                glColor3f(1, 1, 0);

                points.push_back(point(r * x * zr1, r * y * zr1, r * z1));
                points.push_back(point(r * x * zr0, r * y * zr0, r * z0));
            }
            else if (!drawn) {
                drawn = true;
                
                m = (int)(0.5 + 180 + 45 + halfThreshHold);
                               
                double lng = 2 * M_PI * (double) (m - 1) / 360;
                double x = cos(lng);
                double y = sin(lng);

                points.push_back(point(r * x * zr1, r * y * zr1, r * z1));
                points.push_back(point(r * x * zr0, r * y * zr0, r * z0));
                //glColor3f(1,0,0);
                points.push_back(point(r * x * zr1, r * y * zr1, r * z1));
                points.push_back(point(r * x * zr0, r * y * zr0, r * z0));
                points.push_back(point(0, 0, r * z1));
                points.push_back(point(0, 0, r * z0));
                                
                m = (int)(0.5 + 360 - 45 - halfThreshHold);
                
                lng = 2 * M_PI * (double) (m - 1) / 360;
                x = cos(lng);
                y = sin(lng);

                points.push_back(point(r * x * zr1, r * y * zr1, r * z1));
                points.push_back(point(r * x * zr0, r * y * zr0, r * z0));
                //glColor3f(1,1,0);
                points.push_back(point(r * x * zr1, r * y * zr1, r * z1));
                points.push_back(point(r * x * zr0, r * y * zr0, r * z0));                
            }            

        }

    }
    
    glColor3f(1,1,0);
    
    glBegin(GL_QUAD_STRIP);
    for (unsigned int i = 0; i < points.size(); i++) {
        point p = points[i];
        point n;
        computeFaceNormal(&points[i], &points[i+1], &points[i+2], &n);
        glNormal3f(n.x, n.y, n.z);
        glVertex3f(p.x, p.y, p.z);
    }
    glEnd();
    
        
    glBegin(GL_LINES);
    for (unsigned int i = 0; i < points.size(); i++) {
        point p = points[i];
        point n;
        computeFaceNormal(&points[i], &points[i+1], &points[i+2], &n);
        glVertex3f(p.x, p.y, p.z);
        glNormal3f((p.x)+n.x*5, (p.y)+n.y*5, (p.z)+n.z*5);
    }
    glEnd();

    glPopMatrix();
}

Tile * Player::getCurrentTile() {
    return currentTile;
}
