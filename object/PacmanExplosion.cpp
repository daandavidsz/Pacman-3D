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
    alpha = 1.0;
    
    //glDepthMask (GL_FALSE);
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

        for(float j = 0; j < 360; j += 360 / longs) {
            double lng = 2 * M_PI * (double) (j - 1) / 360;
            double x = cos(lng);
            double y = sin(lng);
        
            points.push_back(point(r * x * zr1, r * y * zr1, r * z1));
            points.push_back(point(r * x * zr0, r * y * zr0, r * z0));
        }
    }
    
    for (int i = 0; i < points.size() - 2; i += 2) {
        bool vertical = (((i % 25) / 6) % 2) == 0;
        bool horizontal = ((int)(i / 50) % 8) < 4;
        
        int iVertical = ((i % 25) / 6);
        int iHorizontal = ((int)(i / 50) / 4);
        
        int part = 100 * iVertical + (1+iHorizontal);
        
        part = ((i % 48) / 6) + 100*(i / (48*4));
        
        //std::cout << part << "\n";
    
        srand(part + 100);        
        glColor4f(rand() % 256 / 256.0, rand() % 256 / 256.0, rand() % 256 / 256.0, alpha);   

        glColor4f(1, 1, 0, alpha);   
    
        //srand(2*(horizontal != vertical));     
        
        float angle = (rand() % 100) / 100.0;
        float speed = totalTicks / 100.0 * (rand() % 100);
           
        float xOffset = sin(M_PI * angle) * speed;
        if (rand() % 2 == 1) xOffset = 0 - xOffset;
        float zOffset = cos(M_PI * angle) * speed;
        if (rand() % 2 == 1) zOffset = 0 - zOffset;        
        //float yOffset = 1 * totalTicks * ((rand() % 100) / 100.0);
        
        float yOffset = sin(M_PI * totalTicks) * (2 - totalTicks);
        
        if (yOffset < 0) yOffset = 0 - yOffset;
        
        std::vector<point> polyPoints;
        
        glBegin(GL_POLYGON);
        for (int j = 0; j < 4; j++) {
            point p = points[i + j];
            switch (j) {
                case 2:
                    p = points[i+3]; break;
                case 3:
                    p = points[i+2]; break;                                                            
            }
            polyPoints.push_back(p);
            point n = normalizeVector(p);
            glNormal3f(n.x, n.y, n.z);
            glVertex3f(p.x + xOffset, p.y + yOffset, p.z + zOffset);        
        }
        glEnd();        
                
        for (int j = 0; j < 4; j++) {
            std::vector<point> polyVector;
            polyVector.push_back(polyPoints[(j + 1) % 4]);
            polyVector.push_back(polyPoints[j]);
            polyVector.push_back(point(0, 0, 0));
            glBegin(GL_POLYGON);            
            for (int m = 0; m < polyVector.size(); m++) {
                point p = polyVector[m];
                point n = normalizeVector(p);
                glNormal3f(n.x, n.y, n.z);
                glVertex3f(p.x + xOffset, p.y + yOffset, p.z + zOffset);
            }
            glEnd();                    
        }
    }
    
    //exit(0);
    glPopMatrix();
    //glDepthMask (GL_TRUE);
    totalTicks += ticks;
}

bool PacmanExplosion::completed() {
    return false;
}

