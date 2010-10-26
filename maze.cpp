#include "maze.h"

void Maze::drawLines(float * color, int x, int y, float pointX, float pointY) {
    glLineWidth(1.0);    
    
    float size = 0.50;
    
    float rawPointX = pointX;
    float rawPointY = pointY;    
    pointX += (1.0 - size) / 2.0;    
    pointY += (1.0 - size) / 2.0;  
    
    std::vector<point> points; 
    std::vector<point> ceiling; 
    
    /*
    glColor4f (1.0, 1.0, 0.0, 0.5);
    glBegin (GL_LINE_LOOP);
        glVertex3f(rawPointX, rawPointY, -19);
        glVertex3f(rawPointX, rawPointY + 1.0, -19);
        glVertex3f(rawPointX + 1.0, rawPointY + 1.0, -19);
        glVertex3f(rawPointX + 1.0, rawPointY, -19);                        
    glEnd ();
    */  
    
    float z = -19;
    glColor3f (0.0, 0.0, 1.0);
        
    bool walls[5] = {true, true, true, true, true};
    
    DIRECTION wallDirection = none;
        
    wallDirection = left;
    walls[wallDirection] = !isWall(x-1, y);
    wallDirection = right;    
    walls[wallDirection] = !isWall(x+1, y);
    wallDirection = down;
    walls[wallDirection] = !isWall(x, y-1);  
    wallDirection = up;
    walls[wallDirection] = !isWall(x, y+1);  
    
    // Wall facing up
    if (walls[up] == true && walls[right] == false && walls[left] == false) {
        points.push_back(point(rawPointX+1.0, rawPointY + 0.5));
        points.push_back(point(rawPointX, rawPointY + 0.5));
        points.push_back(point(rawPointX, rawPointY));        
        points.push_back(point(rawPointX+1.0, rawPointY));        
        goto done;
    }

    // Wall facing down
    if (walls[down] == true && walls[right] == false && walls[left] == false) {
        points.push_back(point(rawPointX, rawPointY + 0.5));
        points.push_back(point(rawPointX+1.0, rawPointY + 0.5));
        points.push_back(point(rawPointX+1.0, rawPointY + 1.0));   
        points.push_back(point(rawPointX, rawPointY + 1.0));             
        goto done;
    }
    
    // Wall facing left
    if (walls[left] == true && walls[up] == false && walls[down] == false) {
        points.push_back(point(rawPointX+0.5, rawPointY + 1.0));
        points.push_back(point(rawPointX+0.5, rawPointY));
        points.push_back(point(rawPointX+1.0, rawPointY));        
        points.push_back(point(rawPointX+1.0, rawPointY + 1.0));        
        goto done;
    }
    
    // Wall facing right
    if (walls[right] == true && walls[up] == false && walls[down] == false) {
        points.push_back(point(rawPointX+0.5, rawPointY));
        points.push_back(point(rawPointX+0.5, rawPointY + 1.0));
        points.push_back(point(rawPointX, rawPointY + 1.0));        
        points.push_back(point(rawPointX, rawPointY));                
        goto done;
    }
    
    if (walls[up] || walls[down] || walls[right] || walls[left]) {
        if (walls[up] && walls[left]) {
            drawCorner(rawPointX+0.5, rawPointY+0.5, -19, 90, true);
            
            /*
            glColor4f (1.0, 1.0, 0.0, 0.5);
            glBegin (GL_LINE_LOOP);
                glVertex3f(rawPointX, rawPointY, -19);
                glVertex3f(rawPointX, rawPointY + 1.0, -19);
                glVertex3f(rawPointX + 1.0, rawPointY + 1.0, -19);
                glVertex3f(rawPointX + 1.0, rawPointY, -19);                        
            glEnd ();   
            */
        }
            
        else if (walls[up] && walls[right])
            drawCorner(rawPointX+0.5, rawPointY+0.5, -19, 0, true);
        else if (walls[down] && walls[left])
            drawCorner(rawPointX+0.5, rawPointY+0.5, -19, 180, true);
        else if (walls[down] && walls[right])
            drawCorner(rawPointX+0.5, rawPointY+0.5, -19, 270, true);
    }
    else {
        if (!isWall(x-1, y-1)) {
            drawCorner(rawPointX+0.5, rawPointY+0.5, -19, 0, false);
        }
        else if (!isWall(x+1, y+1)) {
            drawCorner(rawPointX+0.5, rawPointY+0.5, -19, 180, false);
        }
        else if (!isWall(x-1, y+1)) {
            drawCorner(rawPointX+0.5, rawPointY+0.5, -19, 270, false);
        }
        else if (!isWall(x+1, y-1)) {
            drawCorner(rawPointX+0.5, rawPointY+0.5, -19, 90, false);
        }
    }
    
    done:;

    glBegin(GL_QUADS);
    for (unsigned int i = 0; i < points.size(); i++) {
        point p = points[i];
        glColor4f (0, 0.0, 0.5, 0.7);
        glNormal3f(0, 0, 1);
        glVertex3f(p.x, p.y, z-0.02);
    }
    glEnd (); 
    
    glBegin (GL_LINE_STRIP);
    for (unsigned int i = 0; i < points.size() && i < 2; i++) {
        point p = points[i];
        glColor4f (0.0, 0.0, 1.0, 1.0);
        glVertex3f(p.x, p.y, z);
    }
    glEnd (); 
}

void Maze::drawCorner(float xCenter, float yCenter, float z, float start, bool inner) {
	float x,y;
	float radius = 0.5f;
	
	glPushMatrix();
	glTranslatef(xCenter, yCenter, z);
	glRotatef(start, 0, 0, 1);
	
	glBegin(GL_LINE_STRIP);
		x = (float)radius * cos(359 * PI/180.0f);
		y = (float)radius * sin(359 * PI/180.0f);
		for(float j = 0; j <= 90; j += 15)
		{
		    float step = inner ? j : 90 - j;
			x = (float)radius * cos(step * PI/180.0f);
			y = (float)radius * sin(step * PI/180.0f);
			glVertex3f(x-0.5, y-0.5, 0);
		}
	glEnd();
	
	glColor4f(0, 0, 0.5, 0.7);	
	glBegin(GL_POLYGON);
		x = (float)radius * cos(359 * PI/180.0f);
		y = (float)radius * sin(359 * PI/180.0f);
		
		if (!inner) {
	        glNormal3f(0, 0, 1);
    		glVertex3f(-0.5, 0.5, -0.02);
		}
		
		for(float j = 0; j <= 90; j += 15)
		{
		    float step = inner ? j: 90 - j;
			x = (float)radius * cos(step * PI/180.0f);
			y = (float)radius * sin(step * PI/180.0f);
	        glNormal3f(0, 0, 1);
			glVertex3f(x-0.5, y-0.5, -0.02);
		}
		if (inner) {
	        glNormal3f(0, 0, 1);
    		glVertex3f(-0.5, -0.5, -0.02);
		}
		else {
	        glNormal3f(0, 0, 1);
    		glVertex3f(0.5, -0.5, -0.02);	
	        glNormal3f(0, 0, 1);
    		glVertex3f(0.5, 0.5, -0.02);		    		
		}
	glEnd();
	
	glRotatef(-start, 0, 0, 1);
	glPopMatrix();
}

void Maze::createNormal(float x, float y, float z) {
    glNormal3f(x,y,z);
}
        
void Maze::createMaze() {
	glNewList(mazeDisplayList, GL_COMPILE);

    int mazeHeight = getHeight();
    int mazeWidth = getWidth(); 
    
    for (int x = 0; x < mazeWidth; x++) {
        for (int y = 0; y < mazeHeight; y++) {  
            std::cout << x << "->" << y << "\n";        
                  
            float * color = getPixel(x,y);
            
            point center;
            center.x = (float)x - (width / 2 - 0.5);
            center.y = (float)y - (height / 2 - 0.5);
            center.z = -19.5;
            tiles[x][y].setCenter(center);
            pos position;
            position.x = x;
            position.y = y;
            tiles[x][y].setPosition(position);
            tiles[x][y].addListener(this);
            
            float colorSum = color[0] + color[1] + color[2];
            
            if (color[0] == 1.0 && colorSum == 1.0) {
                tiles[x][y].setEnergizer();                
            }
            else if (color[0] == 1.0 && color[1] == 1.0 && color[2] == 0.0) {
                // Dot
            }
            else if (colorSum == 3.0) {
                tiles[x][y].setVisited();            
            }
            else {
                tiles[x][y].setVisited();
                if (colorSum > 0.0) {
                    drawWall(x, y, color);
                }
                else {
                    drawCeiling(x, y);
                }
            }
        }
    }
    
    // Configure exits
    for (int x = 1; x < mazeWidth; x++) {
        for (int y = 1; y < mazeHeight; y++) { 
            if (!isWall(x,y)) {
                if (!isWall(x,y-1)) {     
                    tiles[x][y].setExit(down, &tiles[x][y-1]);
                    tiles[x][y-1].setExit(up, &tiles[x][y]);
                }
                if (!isWall(x-1,y)) {
                    tiles[x][y].setExit(left, &tiles[x-1][y]);
                    tiles[x-1][y].setExit(right, &tiles[x][y]);                    
                }
            }
        }
    }  
    
    for (int x = 0; x < mazeWidth; x++) {
        if (!isWall(x,0) && !isWall(x, mazeHeight-1)) {
            tiles[x][0].setExit(up, &tiles[x][mazeHeight-1]);
            tiles[x][mazeHeight-1].setExit(down, &tiles[x][0]);   
        }
    }
    
    for (int y = 1; y < mazeHeight; y++) { 
        if (!isWall(0,y) && !isWall(mazeWidth - 1, y)) {
            tiles[0][y].setExit(left, &tiles[mazeWidth - 1][y]);
            tiles[mazeWidth - 1][y].setExit(right, &tiles[0][y]);   
        }
    }
    
	glEndList();
}

void Maze::drawCeiling(int x, int y) {
    float pointX = (float)x-(width/2);
    float pointY = (float)y-(height/2);
    float top = -19 - 0.02;
    
    glColor4f(0.0, 0.0, 0.5, 0.7);
    
    glBegin (GL_QUADS);
        glNormal3f(0, 0, 1);
        glVertex3f(pointX, pointY, top);
        glNormal3f(0, 0, 1);        
        glVertex3f(pointX+1, pointY, top);
        glNormal3f(0, 0, 1);        
        glVertex3f(pointX+1, pointY+1, top);
        glNormal3f(0, 0, 1);        
        glVertex3f(pointX, pointY+1, top);
    glEnd ();
}

void Maze::drawWall(int x, int y, float * color) {
    float pointX = (float)x-width/2;
    float pointY = (float)y-height/2;
    glColor4f (color[0], color[1], color[2], 1.0);
    drawLines(color, x, y, pointX, pointY);
}

void Maze::load() {
    mazeDisplayList = glGenLists(1);
    
    Magick::Image img("map.png");
    
    width = (int) img.columns();
    height = (int) img.rows();            

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            float *color;
            color = new float[3];
            Magick::ColorRGB rgb(img.pixelColor(x, y));
            color[0] = rgb.red();
            color[1] = rgb.green();
            color[2] = rgb.blue();
            pixels[x][height - 1  - y] = color;
            pixelColors[x][height - 1 - y] = rgb.red() * 10000 + rgb.green() * 100 + rgb.blue();
        }
    }
    createMaze();
}
        
int Maze::getWidth() {
    return width;
}
        
int Maze::getHeight() {
    return height;
}
        
float * Maze::getPixel(int x, int y) {
    return pixels[x][y];
}

Tile * Maze::getTile(int x, int y) {
    return &tiles[x][y];
}
        
void Maze::render(float ticks, float gameTime) {
    glTranslatef(0,0,-0.5);
    glCallList(mazeDisplayList);
    glTranslatef(0,0,0.5);
    glCallList(mazeDisplayList);

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            tiles[x][y].render(ticks, gameTime);
        }   
    }
}

