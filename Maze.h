#pragma once

#define PI 3.14159265358979323846

#include <GL/glut.h> // Header File For The GLUT Library 
#include <GL/gl.h>	 // Header File For The OpenGL32 Library
#include <GL/glu.h>	 // Header File For The GLu32 Library

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <math.h>

#include <Magick++.h>

#include "actor/Player.h"
#include "Direction.h"
#include "Tile.h"
#include "EventHandler.h"

class Maze : public EventHandler {

    private:
        int width;
        int height;
        float * pixels[28][31];
        float pixelColors[28][31];
        Tile tiles[28][31];
    	GLuint mazeDisplayList;
    	Player player;
        std::map <const char *, int> vertexes;

        void drawLines(float * color, int x, int y, float pointX, float pointY);
        void createNormal(float x, float y, float z);
        void createMaze();
        void drawWall(int x, int y, float *color);
        void drawCeiling(int x, int y);
        
        void drawSmallWall();
        void drawSmallEnd();        
        void drawSmallCorner();        
        void drawBigWall();
        void drawBigCorner();
        void drawBigInset();
        
        std::bitset<9> rotateGrid(std::bitset<9> grid) {
            std::bitset<9> newGrid;
            newGrid[6] = grid[0];
            newGrid[3] = grid[1];
            newGrid[0] = grid[2];
            newGrid[7] = grid[3];
            newGrid[4] = grid[4];
            newGrid[1] = grid[5];
            newGrid[8] = grid[6];
            newGrid[5] = grid[7];
            newGrid[2] = grid[8];                                                                                                
            return newGrid;
        }
        
        bool isWall(int x, int y) {
            if (x < 0 || x >= width || y < 0 || y >= height)
                return true;
            float * color = getPixel(x,y);
            float colorSum = color[0] + color[1] + color[2];
            if (color[0] == 1.0 && colorSum == 1.0) return false;
            if (color[0] == 1.0 && color[1] == 1.0 && color[2] == 0.0) return false;
            return colorSum < 3.0;
        };
        
        void drawCorner(float xCenter, float yCenter, float z, float start, bool inner);

    public:
        void load();
        int getWidth();
        int getHeight();
        float * getPixel(int x, int y);
        void render(float ticks, float gameTime);
        
        Tile * getTile(int x, int y);
        
};
