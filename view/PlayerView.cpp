#include "PlayerView.h"

point PlayerView::normalizeVector(point vector) {
    point normalizedVector;
    float len = (float)(sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z));
    normalizedVector.x = vector.x / len;
    normalizedVector.y = vector.y / len;
    normalizedVector.z = vector.z / len;
    return normalizedVector;
}

void PlayerView::setRotation(double r) {
    rotation = r;
}

void PlayerView::setRadius(double r) {
    radius = r;
}

void PlayerView::render(float direction, float opening, bool draw) {
    glRotatef(90, 0, 1, 0);  
    glRotatef(rotation, 0, 0, 1);      
    glRotatef(direction, 1, 0, 0);
    glRotatef(90, 0, 0, 1);     
    
    if (!draw) return;
            
    std::vector<point> points; 
    std::map<int,bool> mouth;
    
    int lats = 24;
    int longs = 24;

    float i, j;
    
    for(i = 1; i <= lats; i++) {
        double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
        double z0  = sin(lat0);
        double zr0 = cos(lat0);

        double lat1 = M_PI * (-0.5 + (double) i / lats);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);

        bool drawn = false;
        
        float m;

        for(j = 0; j <= 360; j += 360 / longs) {
            if (j <= opening || j >= 360 - opening) {
                double lng = 2 * M_PI * (double) (j - 1) / 360;
                double x = cos(lng);
                double y = sin(lng);
            
                glColor3f(1, 1, 0);

                points.push_back(point(radius * x * zr1, radius * y * zr1, radius * z1));
                points.push_back(point(radius * x * zr0, radius * y * zr0, radius * z0));
            }
            else if (!drawn) {
                drawn = true;
                
                m = (int)(0.5 + opening);
                               
                double lng = 2 * M_PI * (double) (m - 1) / 360;
                double x = cos(lng);
                double y = sin(lng);


                points.push_back(point(radius * x * zr1, radius * y * zr1, radius * z1));
                points.push_back(point(radius * x * zr0, radius * y * zr0, radius * z0));
                mouth[(int)points.size()] = true;
                points.push_back(point(radius * x * zr1, radius * y * zr1, radius * z1));
                points.push_back(point(radius * x * zr0, radius * y * zr0, radius * z0));
                points.push_back(point(0, 0, radius * z1));
                points.push_back(point(0, 0, radius * z0));
                                
                m = (int)(0.5 + 360 - opening);
                
                lng = 2 * M_PI * (double) (m - 1) / 360;
                x = cos(lng);
                y = sin(lng);

                points.push_back(point(radius * x * zr1, radius * y * zr1, radius * z1));
                points.push_back(point(radius * x * zr0, radius * y * zr0, radius * z0));
                
                mouth[(int)points.size()] = false;
                points.push_back(point(radius * x * zr1, radius * y * zr1, radius * z1));
                points.push_back(point(radius * x * zr0, radius * y * zr0, radius * z0));                
            }            
        }
    }

    glColor3f(1,1,0);

    bool isMouth = false;

    glBegin(GL_QUAD_STRIP);
    for (unsigned int i = 0; i < points.size(); i++) {

        if (mouth.find(i) != mouth.end()) {
            switch (mouth.find(i)->second) {
                case true:
                    glColor3f(1, 0, 0);
                    isMouth = true;
                    break;
                case false:
                    glColor3f(1, 1, 0);
                    isMouth = false;
                    break;
            }
        }

        point p = points[i];
        
        point n = normalizeVector(p);
        if (isMouth) {
            glNormal3f(-1, 0, 0);
        }
        else {
            glNormal3f(n.x, n.y, n.z);
        }
        
        glVertex3f(p.x, p.y, p.z);
    }
    glEnd();
}
