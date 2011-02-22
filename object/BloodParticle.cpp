#include "BloodParticle.h"

BloodParticle::BloodParticle() {
    size = 0.04 + 0.06 * (rand() % 100 / 100.0);
    fallen = false;
    splatters = 5 + rand() % 5;
    splatterDirection = (rand() % 100) / 50.0 * M_PI;
}

void BloodParticle::setPosition(Vector _position) {
    position = _position;
}

void BloodParticle::setMovementVector(Vector _movementVector) {
    movementVector = _movementVector;
}

void BloodParticle::update(float ticks) {
    if (fallen) return;

    ticks *= 20;
    position.x += movementVector.x * ticks;
    position.y += movementVector.y * ticks;
    position.z += movementVector.z * ticks;  

    movementVector.y = movementVector.y - ticks/10;

    movementVector.x = movementVector.x * (1 - ticks/50);
    movementVector.y = movementVector.y * (1 - ticks/50);
    movementVector.z = movementVector.z * (1 - ticks/50);
    
    if (position.y < -1) {
        fallen = true;
        position.y = -1;
        movementVector.x = 0;
        movementVector.y = 0;
        movementVector.z = 0;
    }
}

void BloodParticle::render() {
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    glColor3f(1, 0, 0);
    
    glutSolidSphere(size, 6, 6);

    /*
    for (int i = 0; i < splatters; i++) {
        glTranslatef(sin(splatterDirection)*size, 0, cos(splatterDirection)*size);
        glutSolidSphere(size / 3.0, 6, 6);
        glTranslatef(-sin(splatterDirection)*size, 0, -cos(splatterDirection)*size);
    }
    */
	
    glPopMatrix();    
}

