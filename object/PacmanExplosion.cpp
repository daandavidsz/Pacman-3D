#include "PacmanExplosion.h"
#include "Particle.cpp"
#include "BloodParticle.cpp"

PacmanExplosion::PacmanExplosion() {
    reset();
}

void PacmanExplosion::reset() {
    totalTicks = 0;
    std::vector<Vector> points; 
    particles.clear();
    bloodParticles.clear();
    
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

        for(float j = 0; j < 360; j += 360 / longs) {
            double lng = 2 * M_PI * (double) (j - 1) / 360;
            double x = cos(lng);
            double y = sin(lng);
        
            points.push_back(Vector(r * x * zr1, r * y * zr1, r * z1));
            points.push_back(Vector(r * x * zr0, r * y * zr0, r * z0));
        }
    }
    
    for (unsigned int i = 0; i < points.size() - 2; i += 2) {
        int part = ((i % 48) / 6) + 100*(i / (48*4));
        
        if (particles.find(part) == particles.end()) {
            particles[part] = Particle();
            particles[part].setPosition(points[i]);
        }
        
        std::vector<Vector> polyPoints;
        
        for (int j = 0; j < 4; j++) {
            Vector p = points[i + j];
            switch (j) {
                case 2:
                    p = points[i+3]; break;
                case 3:
                    p = points[i+2]; break;                                                            
            }
            polyPoints.push_back(p);
            Vector n = normalizeVector(p);
            particles[part].addQuadPoint(p, n);
        }
                
        for (int j = 0; j < 4; j++) {
            std::vector<Vector> polyVector;
            polyVector.push_back(polyPoints[(j + 1) % 4]);
            polyVector.push_back(polyPoints[j]);
            polyVector.push_back(Vector(0, 0, 0));
            for (unsigned int m = 0; m < polyVector.size(); m++) {
                Vector p = polyVector[m];
                Vector n = normalizeVector(p);
                particles[part].addTrianglePoint(p, n);                
            }
        }
    }
}

Vector PacmanExplosion::normalizeVector(Vector vector) {
    Vector normalizedVector;
    float len = (float)(sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z));
    normalizedVector.x = vector.x / len;
    normalizedVector.y = vector.y / len;
    normalizedVector.z = vector.z / len;
    return normalizedVector;
}

void PacmanExplosion::render(float ticks) {
    glPushMatrix();
    
    for (unsigned int i = 0; i < bloodParticles.size(); i++) {
        bloodParticles[i].update(ticks);
        bloodParticles[i].render();
    }
    
    for (unsigned int i = 0; i < particles.size(); i++) {
        particles[i].update(ticks);
        if (bloodParticles.size() < 300 && rand() % 500 == 1) {
            BloodParticle blood;
            blood.setPosition(particles[i].getPosition());
            Vector movementVector = particles[i].getMovementVector();
            movementVector.x *= 0.5;
            movementVector.y *= 0.5;
            movementVector.z *= 0.5;                        
            blood.setMovementVector(movementVector);   
            bloodParticles.push_back(blood);         
        }
        particles[i].render();
    }
    
    glPopMatrix();
    totalTicks += ticks;
}

bool PacmanExplosion::completed() {
    return false;
}

