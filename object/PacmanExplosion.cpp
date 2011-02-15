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

point PacmanExplosion::normalizeVector(point vector) {
    point normalizedVector;
    float len = (float)(sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z));
    normalizedVector.x = vector.x / len;
    normalizedVector.y = vector.y / len;
    normalizedVector.z = vector.z / len;
    return normalizedVector;
}

void PacmanExplosion::render(float ticks) {
    float alpha = 1.0 - totalTicks*1.2;
    if (alpha < 0.0) {
        alpha = 0.0;
    }
    
    glDepthMask (GL_FALSE);
    glPushMatrix();
    
    std::vector<point> points; 
    double r = 0.7;
    int lats = 24;
    int longs = 24;
    
    for(float i = 1; i <= lats; i++) {
        double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
        double z0  = sin(lat0);
        double zr0 = cos(lat0);

        double lat1 = M_PI * (-0.5 + (double) i / lats);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);

        for(float j = 0; j <= 360; j += 360 / longs) {
            double lng = 2 * M_PI * (double) (j - 1) / 360;
            double x = cos(lng);
            double y = sin(lng);
        
            points.push_back(point(r * x * zr1, r * y * zr1, r * z1));
            points.push_back(point(r * x * zr0, r * y * zr0, r * z0));
        }
    }
    
    srand(1);

    glColor4f(1, 1, 0, alpha);    
    glBegin(GL_QUADS);
    for (int i = 0; i < points.size() - 2; i += 2) {
        float xOffset = 40 * totalTicks * (-0.5 + (rand() % 100) / 100.0);
        float zOffset = 40 * totalTicks * (-0.5 + (rand() % 100) / 100.0);
        float yOffset = 40 * totalTicks * (-0.5 + (rand() % 100) / 100.0);
        for (int j = 0; j < 4; j++) {
            point p = points[i];
            switch (j) {
                case 0:
                    p = points[i+0]; break;
                case 1:
                    p = points[i+1]; break;
                case 2:
                    p = points[i+3]; break;
                case 3:
                    p = points[i+2]; break;                                                            
            }
            point n = normalizeVector(p);
            glNormal3f(n.x, n.y, n.z);
            glVertex3f(p.x + xOffset, p.y + yOffset, p.z + zOffset);        
        }
    }
    glEnd();
    
    glPopMatrix();
    glDepthMask (GL_TRUE);
    totalTicks += ticks;
}

bool PacmanExplosion::completed() {
    return false;
}
