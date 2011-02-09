#include "PacmanExplosion.h"

PacmanExplosionParticle::PacmanExplosionParticle() {
    xShift = -2.0 + (rand() % 100) / 25.0;
    yShift = -2.0 + (rand() % 100) / 25.0;
    zShift = -2.0 + (rand() % 100) / 25.0;
}

void PacmanExplosionParticle::render(float totalTicks) {
    totalTicks = totalTicks * 2;
    glTranslatef(totalTicks * xShift, totalTicks * yShift, totalTicks * zShift);
    glutSolidSphere(0.08, 4, 4);
}

PacmanExplosion::PacmanExplosion() {
    reset();
}

void PacmanExplosion::reset() {
    totalTicks = 0;
    particles.clear();
    for (int i = 0; i < 50; i++) {
        particles.push_back(PacmanExplosionParticle());
    }
}

void PacmanExplosion::render(float ticks) {
    int alpha = std::min(100, (int)(totalTicks * 200));
    
    glDepthMask (GL_FALSE);
    for (int i = 0; i < particles.size(); i++) { 
        glColor4f(1, 1 * i > 15, 0, 1 - (float(alpha) / 100.0));
        glPushMatrix();    
        particles[i].render(totalTicks);
        glPopMatrix();
    }
    glDepthMask (GL_TRUE);
    totalTicks += ticks;
}

bool PacmanExplosion::completed() {
    return false;
}
