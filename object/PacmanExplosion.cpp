#include "PacmanExplosion.h"
#include "Particle.cpp"

PacmanExplosion::PacmanExplosion() {
    reset();
}

void PacmanExplosion::reset() {
    totalTicks = 0;
    std::vector<Vector> points; 
    particles.clear();
    
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
    
    for (int i = 0; i < points.size() - 2; i += 2) {
        int part = ((i % 48) / 6) + 100*(i / (48*4));
        
        if (particles.find(part) == particles.end()) {
            particles[part] = Particle();
            particles[part].setPosition(points[i]);
        }
        particles[part].addPoint(points[i]);
        
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
            particles[part].addPoint(p);
        }
                
        for (int j = 0; j < 4; j++) {
            std::vector<Vector> polyVector;
            polyVector.push_back(polyPoints[(j + 1) % 4]);
            polyVector.push_back(polyPoints[j]);
            polyVector.push_back(Vector(0, 0, 0));
            for (int m = 0; m < polyVector.size(); m++) {
                Vector p = polyVector[m];
                particles[part].addPoint(p);                
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
    float alpha = 1.0 - totalTicks*1.2;
    if (alpha < 0.0) {
        alpha = 0.0;
    }
    alpha = 1.0;
    
    //glDepthMask (GL_FALSE);
    glPushMatrix();
    
    for (int i = 0; i < particles.size(); i++) {
        particles[i].update(ticks);
        particles[i].render();
    }
    
    glPopMatrix();
    //glDepthMask (GL_TRUE);
    totalTicks += ticks;
}

bool PacmanExplosion::completed() {
    return false;
}

