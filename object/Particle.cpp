#include "Particle.h"

Particle::Particle() {
    float direction = M_PI * (rand() % 1000) / 500.0;
    float change = (rand() % 100) / 150.0;

    movementVector.x = sin(direction) * change;
    movementVector.y = (rand() % 100) / 100.0;
    movementVector.z = cos(direction) * change;
}

Vector Particle::getPosition() {
    return position;
}

Vector Particle::getMovementVector() {
    return movementVector;
}

void Particle::addQuadPoint(Vector point, Vector normal) {
    qPoints.push_back(point);
    qNormals.push_back(normal);    
}

void Particle::addTrianglePoint(Vector point, Vector normal) {
    tPoints.push_back(point);
    tNormals.push_back(normal);    
}

void Particle::setPosition(Vector position) {
}

void Particle::update(float ticks) {
    totalTicks += ticks;
    
    ticks *= 20;
    position.x += movementVector.x * ticks;
    position.y += movementVector.y * ticks;
    position.z += movementVector.z * ticks;  

    movementVector.y = movementVector.y - ticks/10;

    movementVector.x = movementVector.x * (1 - ticks/50);
    movementVector.y = movementVector.y * (1 - ticks/50);
    movementVector.z = movementVector.z * (1 - ticks/50);
    
    if (position.y < -1) {
        position.y = -1 - (position.y+1);
        movementVector.y = 0 - movementVector.y;
        movementVector.x *= 0.55;
        movementVector.y *= 0.55;
        movementVector.z *= 0.55;                
    }
}

void Particle::render() {
    glColor3f(1, 1, 0);
    for (int i = 0; i < qPoints.size(); i++) {
        if (i % 4 == 0) {
            glBegin(GL_QUADS);
        }
        Vector p = qPoints[i];
        Vector normal = qNormals[i];
        glNormal3f(normal.x, normal.y, normal.z);
        glVertex3f(p.x + position.x, p.y + position.y, p.z + position.z);
        if (i % 4 == 3) {
            glEnd();
        }        
    }
    
    for (int i = 0; i < tPoints.size(); i++) {
        if (i % 3 == 0) {
            glBegin(GL_TRIANGLES);
        }
        Vector p = tPoints[i];
        Vector normal = tNormals[i];
        glNormal3f(normal.x, normal.y, normal.z);
        glVertex3f(p.x + position.x, p.y + position.y, p.z + position.z);
        if (i % 3 == 2) {
            glEnd();
        }        
    }
}
