#include "Particle.h"

Particle::Particle() {
    float direction = M_PI * (rand() % 1000) / 500.0;
    float change = (rand() % 100) / 100.0;

    movementVector.x = sin(direction) * change;
    movementVector.y = (rand() % 100) / 100.0;
    movementVector.z = cos(direction) * change;
}

void Particle::addPoint(Vector point, Vector normal) {
    points.push_back(point);
    normals.push_back(normal);    
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
        Vector normal = normals[i];
        glNormal3f(normal.x, normal.y, normal.z);
        glVertex3f(p.x + position.x, p.y + position.y, p.z + position.z);
        if (i % 4 == 3) {
            glEnd();
        }        
    }

}
