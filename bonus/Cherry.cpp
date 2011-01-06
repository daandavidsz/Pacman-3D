#include "Cherry.h"

void Cherry::render(float ticks, float gameTime) {
    float height = 0.2 * sin(M_PI * (gameTime * 1.5));
    glTranslatef(0, 0, height);

    glRotatef((int)(gameTime * 180) % 360, 0, 0, 1);    
    
    glColor3f(0.65, 0, 0);
    glTranslatef(-0.3, -0.3, 0);
    glutSolidSphere(0.40, 12, 12);    
    glTranslatef(0.6, 0.6, 0);
    glutSolidSphere(0.40, 12, 12);      
    
    glColor3f(0, 0.65, 0);
    
    GLUquadricObj *quadobj;
    quadobj = gluNewQuadric();
    
    glRotatef(-45, 0, 0, 1);    
    glRotatef(35, 1, 0, 0);    

    gluCylinder(quadobj, 0.07, 0.07, 1.3, 8, 8);
    
    glRotatef(-24, 1, 0, 0);     
    glRotatef(45, 0, 0, 1);       
    glTranslatef(-0.6, -0.6, 0);
    glRotatef(-45, 0, 0, 1);    
    glRotatef(-24, 1, 0, 0);      
    
    gluCylinder(quadobj, 0.07, 0.07, 1.1, 8, 8);
    
    gluDeleteQuadric(quadobj);	
}


