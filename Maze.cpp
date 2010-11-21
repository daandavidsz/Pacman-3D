#include "Maze.h"

void Maze::drawSmallWall() {
    std::vector<point> points; 
    points.push_back(point(0.5, 0.30));
    points.push_back(point(-0.5, 0.30));
    points.push_back(point(-0.5, -0.30));        
    points.push_back(point(0.5, -0.30));      

    glBegin (GL_LINE_LOOP);
    for (unsigned int i = 0; i < points.size(); i++) {
        point p = points[i];
        glColor4f (0.0, 0.0, 1.0, 1.0);
        glVertex3f(p.x, p.y, 0);
    }
    glEnd ();
          
    glBegin(GL_QUADS);
    for (unsigned int i = 0; i < points.size(); i++) {
        point p = points[i];
        glColor4f (0, 0.0, 0.5, 0.7);
        glNormal3f(0, 0, 1);
        glVertex3f(p.x, p.y, -0.02);
    }
    glEnd (); 
}

void Maze::drawSmallCorner() {
    std::vector<point> points; 
    points.push_back(point(-0.3, 0.5));
    points.push_back(point(-0.3, -0.3));
    points.push_back(point(0.5, -0.3));        
    points.push_back(point(0.5, 0.3));      
    points.push_back(point(0.3, 0.3));                  
    points.push_back(point(0.3, 0.5));                              

    glBegin (GL_LINE_LOOP);
    for (unsigned int i = 0; i < points.size(); i++) {
        point p = points[i];
        glColor4f (0.0, 0.0, 1.0, 1.0);
        glVertex3f(p.x, p.y, 0);
    }
    glEnd ();
          
    glBegin(GL_POLYGON);
    for (unsigned int i = 0; i < points.size(); i++) {
        point p = points[i];
        glColor4f (0, 0.0, 0.5, 0.7);
        glNormal3f(0, 0, 1);
        glVertex3f(p.x, p.y, -0.02);
    }
    glEnd (); 
}

void Maze::drawBigWall() {
    std::vector<point> points; 
    points.push_back(point(0.5, 0));
    points.push_back(point(-0.5, 0));
    points.push_back(point(-0.5, 0.5));        
    points.push_back(point(0.5, 0.5));      

    glBegin (GL_LINE_LOOP);
        glColor4f (0.0, 0.0, 1.0, 1.0);    
        glVertex3f(points[0].x, points[0].y, 0);
        glVertex3f(points[1].x, points[1].y, 0);        
    glEnd ();
          
    glBegin(GL_QUADS);
    for (unsigned int i = 0; i < points.size(); i++) {
        point p = points[i];
        glColor4f (0, 0.0, 0.5, 0.7);
        glNormal3f(0, 0, 1);
        glVertex3f(p.x, p.y, -0.02);
    }
    glEnd (); 
}

void Maze::drawBigCorner() {
    std::vector<point> points; 
    points.push_back(point(0.5, 0.5));
    points.push_back(point(0.5, 0));
    points.push_back(point(0, 0.5));        

    glBegin (GL_LINE_LOOP);
        glColor4f (0.0, 0.0, 1.0, 1.0);
        glVertex3f(points[1].x, points[1].y, 0);
        glVertex3f(points[2].x, points[2].y, 0);        
    glEnd ();
          
    glBegin(GL_POLYGON);
    for (unsigned int i = 0; i < points.size(); i++) {
        point p = points[i];
        glColor4f (0, 0.0, 0.5, 0.7);
        glNormal3f(0, 0, 1);
        glVertex3f(p.x, p.y, -0.02);
    }
    glEnd (); 
}

void Maze::drawBigInset() {
    std::vector<point> points; 
    points.push_back(point(0.5, -0.5));
    points.push_back(point(0, -0.5));
    points.push_back(point(-0.5, 0));        
    points.push_back(point(-0.5, 0.5));                    
    points.push_back(point(0.5, 0.5));                                

    glBegin (GL_LINE_LOOP);
        glColor4f (0.0, 0.0, 1.0, 1.0);
        glVertex3f(points[1].x, points[1].y, 0);
        glVertex3f(points[2].x, points[2].y, 0);        
    glEnd ();
          
    glBegin(GL_POLYGON);
    for (unsigned int i = 0; i < points.size(); i++) {
        point p = points[i];
        glColor4f (0, 0.0, 0.5, 0.7);
        glNormal3f(0, 0, 1);
        glVertex3f(p.x, p.y, -0.02);
    }
    glEnd (); 
}

void Maze::drawLines(float * color, int x, int y, float pointX, float pointY) {
    glLineWidth(1.0);    
    
    std::bitset<9> grid;
        
    if (isWall(x-1, y-1)) grid[0] = 1;
    if (isWall(x+0, y-1)) grid[1] = 1;
    if (isWall(x+1, y-1)) grid[2] = 1;
    if (isWall(x-1, y+0)) grid[3] = 1;
    if (isWall(x+0, y+0)) grid[4] = 1;
    if (isWall(x+1, y+0)) grid[5] = 1;
    if (isWall(x-1, y+1)) grid[6] = 1;
    if (isWall(x+0, y+1)) grid[7] = 1;
    if (isWall(x+1, y+1)) grid[8] = 1;
    
    float size = 0.50;
    
    float rawPointX = pointX;
    float rawPointY = pointY;    
    pointX += (1.0 - size) / 2.0;    
    pointY += (1.0 - size) / 2.0;  
    
    std::vector<point> points; 
    
    float z = -19;
    glColor3f (0.0, 0.0, 1.0);
    
    int counter = 0;
    while (true) {
        std::cout << counter << "\n";
        int drawType = counter / 4;
        float rotation = (counter % 4) * 90;
        
        switch (drawType) {
            case 0: // Small wall
                if (!grid[1] && !grid[7] && (grid[3] || grid[5])) {
                    glPushMatrix();
                    glTranslatef(rawPointX+0.5, rawPointY+0.5, z);
                    glRotatef(rotation, 0, 0, 1);
                    
                    drawSmallWall();
                    
                    glRotatef(0 - rotation, 0, 0, 1);
                	glPopMatrix();
                    return;
                }
                break;
            case 1: // 90 degree corner
                if (!grid[1] && grid[7] && !grid[3] && grid[5] && !grid[8])        
                {
                    glPushMatrix();
                    glTranslatef(rawPointX+0.5, rawPointY+0.5, z);
                    glRotatef(rotation, 0, 0, 1);
                    
                    drawSmallCorner();
                    
                    glRotatef(0 - rotation, 0, 0, 1);
                	glPopMatrix();
                    return;
                }
                break;
            case 2: // Big wall
                if (!grid[1] && grid[7] && grid[3] && grid[5]) {
                    glPushMatrix();
                    glTranslatef(rawPointX+0.5, rawPointY+0.5, z);
                    glRotatef(rotation, 0, 0, 1);
                    
                    drawBigWall();
                    
                    glRotatef(0 - rotation, 0, 0, 1);
                	glPopMatrix();
                    return;
                }
                break;
            case 3: // Big corner
               if (!grid[1] && grid[7] && !grid[3] && grid[5]) {
                    glPushMatrix();
                    glTranslatef(rawPointX+0.5, rawPointY+0.5, z);
                    glRotatef(rotation, 0, 0, 1);
                    
                    drawBigCorner();
                                
                    glRotatef(0 - rotation, 0, 0, 1);
                	glPopMatrix();
                    return;
                }
                break;
            case 4: // Big inset
                if (grid.count() == 8 && !grid[0]) {
                    glPushMatrix();
                    glTranslatef(rawPointX+0.5, rawPointY+0.5, z);
                    glRotatef(rotation, 0, 0, 1);
                    
                    drawBigInset();
                    
                    glRotatef(0 - rotation, 0, 0, 1);
                	glPopMatrix();
                    return;
                }
                break;
            default:
                return;
        }
        grid = rotateGrid(grid);
        counter++;
    }
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
		    float step = inner ? j : 90 - j;
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

