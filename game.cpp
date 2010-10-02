#include "game.h"

void Game::load() {
    srand ( time(NULL) );
    maze.load();
    player.setCurrentTile(maze.getTile(1,1));

    blinky.setCurrentTile(maze.getTile(10,10));
    blinky.setPlayer(&player); 
    blinky.start();
    pinky.setCurrentTile(maze.getTile(13,13));
    pinky.setPlayer(&player);  
    pinky.start();
    inky.setCurrentTile(maze.getTile(15,13));
    inky.setPlayer(&player);  
    inky.setBlinky(&blinky);
    inky.start();
    clyde.setCurrentTile(maze.getTile(15,13));
    clyde.setPlayer(&player);  
    clyde.start();
}

Maze Game::getMaze() {
    return maze;
}

void Game::render(float ticks) {
    gameTime += ticks;
    counter++;
    
    /*
    if (gameTime > 5) {
        sleep(100);
    }
    */

    point playerPos = player.getPosition();
    float lookAt = 1 + gameTime * 2.5;
    if (lookAt > 25) lookAt = 25;
    
    // gluLookAt (playerPos.x, playerPos.y, -18.0 + lookAt, playerPos.x/2, playerPos.y/2, playerPos.z, 0.0, 1.0, 0.0);
    // gluLookAt (0, -24, -18.0 + lookAt, 0, -4, playerPos.z, 0.0, 1.0, 0.0);
    // gluLookAt (playerPos.x , playerPos.y - 15, -8, playerPos.x , playerPos.y, playerPos.z, 0.0, 1.0, 0.0);
    
    // gluLookAt (0, -20, 18, 0, -2, playerPos.z, 0.0, 1.0, 0.0);
    
    gluLookAt (playerPos.x, playerPos.y - 16, -4, playerPos.x, playerPos.y, playerPos.z, 0.0, 1.0, 0.0);
    point blinkyPos = blinky.getPosition();
    //gluLookAt (blinkyPos.x, blinkyPos.y - 4, blinkyPos.z+1, blinkyPos.x, blinkyPos.y, blinkyPos.z, 0.0, 1.0, 0.0);
    
    //gluLookAt (blinkyPos.x - 2, blinkyPos.y - 2, blinkyPos.z+4, blinkyPos.x, blinkyPos.y, blinkyPos.z, 0.0, 1.0, 0.0);                                        
    
    maze.render(ticks);
    
    bool scatter = (int)gameTime % (20+7) <= 7;
    blinky.setScatter(scatter); 
    blinky.render(ticks);
    pinky.setScatter(scatter); 
    pinky.render(ticks);
    inky.setScatter(scatter); 
    inky.render(ticks);
    clyde.setScatter(scatter); 
    clyde.render(ticks);

    player.render(ticks);
    
    glEnable ( GL_LIGHTING ) ;            
    //GLfloat position[] = { 0.0, 0.0, -1.0, 1.0f };
    GLfloat position[] = { 0.0, 0.0, 20, 1.0f };            
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    
    GLfloat ambient[] = {0.0, 0.0, 0.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    
    GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    
    GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    
    glEnable(GL_LIGHT0);
    
    glMateriali(GL_FRONT, GL_SHININESS, 96);
    float mcolor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, mcolor); 
    
    glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;
    glEnable ( GL_COLOR_MATERIAL ) ;  

    /*
    glTranslatef(0,-8,0);    
    glMateriali(GL_FRONT, GL_SHININESS, 40);
    float mcolor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, mcolor);
    glutSolidSphere(3, 32, 32);
    
    glTranslatef(6,0,0);  
    glutSolidTorus(1,2+gameTime / 10,24,128);
    */
}

void Game::handleSpecialKeystoke(int key) {
    switch (key) {
        case GLUT_KEY_UP:
            player.setWantedDirection(up); break;
        case GLUT_KEY_DOWN:
            player.setWantedDirection(down); break;
        case GLUT_KEY_LEFT:
            player.setWantedDirection(left); break;
        case GLUT_KEY_RIGHT:
            player.setWantedDirection(right); break;
    }
}

void Game::handleKeystroke(unsigned char key) {
    switch (key) {
        case 'w':
            player.setWantedDirection(up); break;
        case 's':
            player.setWantedDirection(down); break;
        case 'a':
            player.setWantedDirection(left); break;
        case 'd':
            player.setWantedDirection(right); break;
    }
}
