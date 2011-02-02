#include "Game.h"

void Game::load() {
    srand ( time(NULL) );
    maze.load();
    maze.addListener(this);
    
    maze.addListener(&scoreBoard);
    
    player.setGame(this);
    player.setCurrentTile(maze.getTile(1,1));

    blinky.setGame(this);
    blinky.setCurrentTile(maze.getTile(10,10));
    blinky.setPlayer(&player); 
    blinky.start();
    
    pinky.setGame(this);
    pinky.setCurrentTile(maze.getTile(13,13));
    pinky.setPlayer(&player);  
    pinky.start();
    
    inky.setGame(this);
    inky.setCurrentTile(maze.getTile(15,13));
    inky.setPlayer(&player);  
    inky.setBlinky(&blinky);
    inky.start();
    
    clyde.setGame(this);
    clyde.setCurrentTile(maze.getTile(15,13));
    clyde.setPlayer(&player);  
    clyde.start();

    enemies.push_back(&blinky);
    enemies.push_back(&pinky);
    enemies.push_back(&inky);
    enemies.push_back(&clyde);
    for (unsigned int i = 0; i < enemies.size(); i++) {
        this->addListener(enemies[i]);
    }
    
    gameState = running;
}

Maze Game::getMaze() {
    return maze;
}

void Game::onSignal(std::string name) {

}

void Game::handleLighting() {
    glEnable ( GL_LIGHTING ) ;            
        
    GLfloat position[] = { 0.5, -0.3, 1, 0};            
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    
    GLfloat ambient[] = {0.1, 0.1, 0.1};
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
}

void Game::render(float ticks) {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    gameTime += ticks;
    counter++;

    scoreBoard.render(ticks);
    point playerPos = player.getPosition();
    float lookAt = 1 + gameTime * 2.5;
    if (lookAt > 25) lookAt = 25;
    
    //gluLookAt (playerPos.x, playerPos.y, -18.0 + lookAt, playerPos.x/2, playerPos.y/2, playerPos.z, 0.0, 1.0, 0.0);
    //gluLookAt (0, -20, 18, 0, -2, playerPos.z, 0.0, 1.0, 0.0);
    // Close
    
    handleLighting();
    
    gluLookAt (playerPos.x / 3.5, playerPos.y - 16, -4, playerPos.x / 3.5, playerPos.y, playerPos.z, 0.0, 1.0, 0.0);
        
    player.render(ticks);          
            
    for (unsigned int i = 0; i < enemies.size(); i++) {
        enemies[i]->render(ticks);
    }

    maze.render(ticks, gameTime);
    
    for (unsigned int i = 0; i < enemies.size(); i++) {
        pos a = player.getCurrentTile()->getPosition();
        pos b = enemies[i]->getCurrentTile()->getPosition();
        
        float diffX = (float)a.x - (float)b.x;
        float diffY = (float)a.y - (float)b.y;    
        if (diffX < 0.0) diffX = 0.0-diffX;
        if (diffY < 0.0) diffY = 0.0-diffY;

        float distance = sqrt((diffX*diffX) + (diffY*diffY));

        if (distance < 1.1) { 
            gameState = stopped;
            break;
        }
    }
    
    glLoadIdentity();
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
    
    if (paused) {
        paused = false;
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
        case 'p':
            paused = !paused; break;
    }
    
    if (paused && key != 'p') {
        paused = false;
    }
}

bool Game::isPaused() {
    return paused;
}

GAMESTATE Game::getState() {
    return gameState;
}
