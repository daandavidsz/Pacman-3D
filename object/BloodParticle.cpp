#include "BloodParticle.h"

void BloodParticle::setPosition(Vector _position) {
    position = _position;
}

void BloodParticle::setMovementVector(Vector _movementVector) {
    movementVector = _movementVector;
}

void BloodParticle::update(float ticks) {
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

void BloodParticle::render() {
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    glColor3f(1, 0, 0);
    glutSolidSphere(0.06, 6, 6);
    glPopMatrix();    
}

