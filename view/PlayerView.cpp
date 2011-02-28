#include "PlayerView.h"

void PlayerView::render(float direction, float opening) {
    double r = 0.7;
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
            if (j <= threshHold || j >= 360 - threshHold) {
                double lng = 2 * M_PI * (double) (j - 1) / 360;
                double x = cos(lng);
                double y = sin(lng);
            
                glColor3f(1, 1, 0);

                points.push_back(point(r * x * zr1, r * y * zr1, r * z1));
                points.push_back(point(r * x * zr0, r * y * zr0, r * z0));
            }
            else if (!drawn) {
                drawn = true;
                
                m = (int)(0.5 + threshHold);
                               
                double lng = 2 * M_PI * (double) (m - 1) / 360;
                double x = cos(lng);
                double y = sin(lng);


                points.push_back(point(r * x * zr1, r * y * zr1, r * z1));
                points.push_back(point(r * x * zr0, r * y * zr0, r * z0));
                //glColor3f(1,0,0);
                mouth[(int)points.size()] = true;
                points.push_back(point(r * x * zr1, r * y * zr1, r * z1));
                points.push_back(point(r * x * zr0, r * y * zr0, r * z0));
                points.push_back(point(0, 0, r * z1));
                points.push_back(point(0, 0, r * z0));
                                
                m = (int)(0.5 + 360 - threshHold);
                
                lng = 2 * M_PI * (double) (m - 1) / 360;
                x = cos(lng);
                y = sin(lng);

                points.push_back(point(r * x * zr1, r * y * zr1, r * z1));
                points.push_back(point(r * x * zr0, r * y * zr0, r * z0));
                
                mouth[(int)points.size()] = false;
                //glColor3f(1,1,0);
                points.push_back(point(r * x * zr1, r * y * zr1, r * z1));
                points.push_back(point(r * x * zr0, r * y * zr0, r * z0));                
            }            
        }
    }

    glColor4f(1,1,0, alpha);

    bool isMouth = false;

    glBegin(GL_QUAD_STRIP);
    for (unsigned int i = 0; i < points.size(); i++) {

        if (mouth.find(i) != mouth.end()) {
            switch (mouth.find(i)->second) {
                case true:
                    glColor4f(1, 0, 0, alpha);
                    isMouth = true;
                    break;
                case false:
                    glColor4f(1, 1, 0, alpha);
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
