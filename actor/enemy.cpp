#include "enemy.h"

void Enemy::setCurrentTile(Tile * tile) {
    currentTile = tile;
}

void Enemy::setPlayer(Player * p) {
    player = p;
}

point Enemy::getPosition() {
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

void Enemy::start() {
    resolvePosition(0.0);
}

void Enemy::resolveScaredPosition(float ticks) {
    std::vector<DIRECTION> directions;
    DIRECTION dirs[] = {up, down, left, right};
    DIRECTION dir = none;

    int distance = 0;
    for (int i = 0; i < 4; i++) {
        if (currentTile->hasExit(dirs[i])) {
            float thisDistance = this->distance(currentTile->getExit(dirs[i])->getPosition(), player->getCurrentTile()->getPosition());
            if (!this->isOpposite(dirs[i], direction)) directions.push_back(dirs[i]);
            if (thisDistance > distance && !this->isOpposite(dirs[i], direction)) {
                dir = dirs[i];
                distance = thisDistance;
            }
        }
    }

    direction = dir;  
}

void Enemy::resolvePosition(float ticks) {
    std::vector<DIRECTION> directions;
    DIRECTION dirs[] = {up, down, left, right};
    DIRECTION dir = none;

    int distance = 99;
    for (int i = 0; i < 4; i++) {
        if (currentTile->hasExit(dirs[i])) {
            float thisDistance = this->distance(currentTile->getExit(dirs[i])->getPosition(), getTargetPosition());
            if (!this->isOpposite(dirs[i], direction)) directions.push_back(dirs[i]);
            if (thisDistance < distance && !this->isOpposite(dirs[i], direction)) {
                dir = dirs[i];
                distance = thisDistance;
            }
        }
    }

    direction = dir;    
}

pos Enemy::getTargetPosition() {
    if (state == SCATTER) {
        pos p;
        p.x = 0;
        p.y = 0;
        return p;
    }
    return player->getCurrentTile()->getPosition();
}

void Enemy::reverseDirection() {
    currentTile = currentTile->getExit(direction);
    direction = getOpposite(direction);
    position = 1.0 - position;
}

void Enemy::onSignal(std::string name) {
    if (name == "energizer" && state != EATEN) {
        if (state != SCARED) {
            reverseDirection();
        }
        scaredTime = 8;
        state = SCARED;
    }
}

void Enemy::setColor() {
    if (state == SCARED) {
        bool white = scaredTime < 3 && (int)((3.0-scaredTime) * (3.0-scaredTime)) % 2 == 0;
        glColor3f((int)white, (int)white, 1);
    }
    else {
        setRealColor();
    }
}

void Enemy::setRealColor() {
    glColor3f(1, 1, 1);
}

void Enemy::render(float ticks) {
    gameTime += ticks;
    float speed = 7.0;
    if (state == SCARED) speed = 3.5;

    totalTicks += ticks * speed;
    
    if (state == EATEN) {
        if (currentTile->getPosition().x >= 14 && currentTile->getPosition().x <= 16
         && currentTile->getPosition().y >= 14 && currentTile->getPosition().y <= 16) {
            state = CHASE;
        }
    }
    
    if (state == SCARED && scaredTime > 0) {
        scaredTime -= ticks;
        if (scaredTime <= 0) {
            reverseDirection();
        }
    }
    else if (state != EATEN) {
        int mod = (int)gameTime % 27;

        if (mod <= 7) {
            state = SCATTER;
        }
        else {
            state = CHASE;
        }
    }
    
    if (state == SCARED) {
        float distance = this->distance(currentTile->getPosition(), player->getCurrentTile()->getPosition());
        if (distance < 1) {
            state = EATEN;
        }
    }

    if (direction != none) {
        position += ticks * speed;
    }
    if (position >= 1.0) {
        position--;
        currentTile = currentTile->getExit(direction);
        
        DIRECTION tDirection = direction;
        if (state == SCARED) {
            resolveScaredPosition(ticks * speed);
        }
        else {
            this->resolvePosition(ticks * speed);
        }
        if (direction == none) direction = getOpposite(tDirection);
    }

    point center = currentTile->getCenter();
    
    switch (direction) {
        case right: center.x += position; break;
        case left: center.x -= position; break;
        case up: center.y += position; break;
        case down: center.y -= position; break;                
        default: break;        
    }
    
    this->setColor();
    //glColor4f(0,0,1,1);
    
    /*
    glBegin(GL_LINES);            
    glVertex3f(currentTile->getPosition().x-14, currentTile->getPosition().y-15, -19);
    glVertex3f(targetPosition.x-14, targetPosition.y-15, -19);    
    glEnd();
    */

    glPushMatrix();
    glLineWidth(0.5);
    
    float delta = (totalTicks / 3 - (int)(totalTicks / 3));
    float height = 0.2 * sin(M_PI * delta);
        
    glTranslatef(center.x, center.y, -19.4 + height);
    
    switch (direction) {
        case down:
            glRotatef(90,0,0,1); break;
        case up:
            glRotatef(270,0,0,1); break;
        case left:
            glRotatef(0,0,0,1); break;
        case right:
            glRotatef(180,0,0,1); break;                            
    }
    
    if (state != EATEN) {
        renderBody();
    }
    renderEyes();
    glPopMatrix();
}

void Enemy::renderBody() {
    double r = 0.6;
    int lats = 12;
    int longs = 16;
    float i, j;
    
    // Ghost rotation
    //glRotatef(360.0/8*delta,0,0,1);
    
    // Ugly
    //glRotatef(270,0,0,1);

    std::vector<point> points; 
            
    for(i = lats/2; i <= lats; i++) {
        double lat0, z0, zr0;
        
        if (i == lats / 2) {
            double d = lats / 2;
            lat0 = M_PI * (-0.5 + (double) (d) / lats);
            z0  = sin(M_PI * (-0.5 + (double)1.0 / lats));
            zr0 = cos(lat0);
        }
        else {
            lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
            z0  = sin(lat0);
            zr0 = cos(lat0);        
        }

        double lat1 = M_PI * (-0.5 + (double) i / lats);
        double z1 = sin(M_PI * (-0.5 + (double) i / lats));
        double zr1 = cos(lat1);
        
        glBegin(GL_QUAD_STRIP);
        bool odd = true;        
        for(j = 0; j <= 360; j += 360.0 / longs) {
            double lng = 2 * M_PI * (double) (j - 1) / 360;
            double x = cos(lng);
            double y = sin(lng);
            
            double extend = 0;
            if (i == lats / 2 && odd) {
                extend = 0.2;
            }
            
            points.push_back(point(r * x * zr0, r * y * zr0, r * z0 + extend));
            points.push_back(point(r * x * zr1, r * y * zr1, r * z1));
            
            odd = !odd;
        }
        glEnd();
    }
    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    std::vector<point> normals; 
    
    unsigned int counter = 0;
    while (counter < points.size()) {
        point normal;
        computeFaceNormal(&points[counter], &points[counter+2], &points[counter+3], &normal);
        
        point face = points[counter];
        face.x = (face.x + points[counter+3].x) / 2;
        face.y = (face.y + points[counter+3].y) / 2;
        face.z = (face.z + points[counter+3].z) / 2;  
    
        /*
        glColor3f(0,0,1);
        glBegin(GL_LINES);
            glVertex3f(face.x, face.y, face.z);            
            glVertex3f(face.x + normal.x*2, face.y + normal.y*2, face.z + normal.z*2);  
        glEnd();
        glColor3f(1,0,0);      
        */
        
        normals.push_back(normal);        
        
        counter += 2;  
        
        if (counter+2 % longs == 0) counter += 2;
    }
    
    for (i = 0; i < longs; i++) {
        point normal;
        normal.x = 0;
        normal.y = 0;
        normal.z = 1;
        normals.push_back(normal);        
    }
    
    counter = 0;
    while (counter < points.size()-2) {
    
        int vc = counter / 2;
            
        
        glBegin(GL_POLYGON);

        //glNormal3f(normal.x, normal.y, normal.z);

        point vNormalA = computeVertexNormal(normals[vc-longs-2], normals[vc-longs-1], normals[vc], normals[vc-1]);

        glNormal3f(vNormalA.x, vNormalA.y, vNormalA.z);
        glVertex3f(points[counter].x, points[counter].y, points[counter].z);        
        
        vc = counter / 2 + 1;
        point vNormalD = computeVertexNormal(normals[vc-longs-2], normals[vc-longs-1], normals[vc], normals[vc-1]);
        glNormal3f(vNormalD.x, vNormalD.y, vNormalD.z);  
        glVertex3f(points[counter+2].x, points[counter+2].y, points[counter+2].z);          
                      
        vc = counter / 2 + longs + 2;
        point vNormalC = computeVertexNormal(normals[vc-longs-2], normals[vc-longs-1], normals[vc], normals[vc-1]);
        glNormal3f(vNormalC.x, vNormalC.y, vNormalC.z);  
        glVertex3f(points[counter+3].x, points[counter+3].y, points[counter+3].z);                    
        
        vc = counter / 2 + longs + 1;
        point vNormalB = computeVertexNormal(normals[vc-longs-2], normals[vc-longs-1], normals[vc], normals[vc-1]);
        glNormal3f(vNormalB.x, vNormalB.y, vNormalB.z);
        glVertex3f(points[counter+1].x, points[counter+1].y, points[counter+1].z);        
        
        glEnd();
        
        /*
        if (counter < longs) {
            
            glColor3f(0,0,1);
            glBegin(GL_LINES);
                glVertex3f(points[counter+2].x, points[counter+2].y, points[counter+2].z);  
                glVertex3f(points[counter+2].x + vNormalD.x, points[counter+2].y + vNormalD.y, points[counter+2].z + vNormalD.z);  
            glEnd();
            
            glColor3f(0,1,0);
            glBegin(GL_LINES);
                glVertex3f(points[counter+3].x, points[counter+3].y, points[counter+3].z);            
                glVertex3f(points[counter+3].x + vNormalC.x, points[counter+3].y + vNormalC.y, points[counter+3].z + vNormalC.z);  
            glEnd();
            
            glColor3f(1,1,1);
            glBegin(GL_LINES);
                glVertex3f(points[counter+1].x, points[counter+1].y, points[counter+1].z);            
                glVertex3f(points[counter+1].x + vNormalB.x, points[counter+1].y + vNormalB.y, points[counter+1].z + vNormalB.z);  
            glEnd();
            
            glColor3f(1,1,0);
            glBegin(GL_LINES);
                glVertex3f(points[counter].x, points[counter].y, points[counter].z);            
                glVertex3f(points[counter].x + vNormalA.x, points[counter].y + vNormalA.y, points[counter].z + vNormalA.z);  
            glEnd();
            
            glColor3f(1,0,0);
        }
        */
        
        counter += 2;
    }
}

void Enemy::renderEyes() {
    glColor3f(1, 1, 1);
    glTranslatef(-0.40, 0.15, 0.1);
    glutSolidSphere(0.25, 8, 8);

    glTranslatef(0, -0.3, 0);
    glutSolidSphere(0.25, 8, 8);
            
    glColor3f(0, 0, 0);    
    glTranslatef(-0.22, -0.035, 0);
    glutSolidSphere(0.05, 8, 8);
    
    glTranslatef(0, 0.035+0.3, 0);
    glutSolidSphere(0.05, 8, 8);
}

Tile * Enemy::getCurrentTile() {
    return currentTile;
}
