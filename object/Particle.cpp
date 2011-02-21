#include "Particle.h"

Particle::Particle() {
    movementVector.x = -0.5 + (rand() % 100) / 100.0;
    movementVector.y = (rand() % 100) / 100.0;
    movementVector.z = -0.5 + (rand() % 100) / 100.0;    
}

void Particle::addPoint(Vector point) {
    points.push_back(point);
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
}

void Particle::render() {
    glColor3f(1, 1, 0);
    for (int i = 0; i < points.size(); i++) {
        if (i % 4 == 0) {
            glBegin(GL_QUADS);
        }
        Vector p = points[i];
        glVertex3f(p.x + position.x, p.y + position.y, p.z + position.z);
        if (i % 4 == 3) {
            glEnd();
        }        
    }

}
