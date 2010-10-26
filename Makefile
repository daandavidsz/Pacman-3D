CXX=g++
CXXFLAGS=-Wall -Wno-unused-parameter -Wno-switch -lglut -lGLU -lGL `Magick++-config --cppflags --cxxflags --ldflags --libs`

all: Pacman

Pacman: Pacman.cpp EventHandler.o Actor.o Enemy.o Player.o Blinky.o Inky.o Pinky.o Clyde.o Maze.o Game.o Tile.o
		$(CXX) $(CXXFLAGS) Pacman.cpp EventHandler.o Actor.o Enemy.o Player.o Blinky.o Inky.o Pinky.o Clyde.o Maze.o Game.o Tile.o -o Pacman
		
Actor.o: actor/Actor.cpp
		$(CXX) $(CXXFLAGS) -c actor/Actor.cpp

Player.o: actor/Player.cpp
		$(CXX) $(CXXFLAGS) -c actor/Player.cpp
		
Enemy.o: actor/Enemy.cpp
		$(CXX) $(CXXFLAGS) -c actor/Enemy.cpp		
		
Blinky.o: actor/Blinky.cpp
		$(CXX) $(CXXFLAGS) -c actor/Blinky.cpp
		
Inky.o: actor/Inky.cpp
		$(CXX) $(CXXFLAGS) -c actor/Inky.cpp		
		
Pinky.o: actor/Pinky.cpp
		$(CXX) $(CXXFLAGS) -c actor/Pinky.cpp

Clyde.o: actor/Clyde.cpp
		$(CXX) $(CXXFLAGS) -c actor/Clyde.cpp
		
EventHandler.o: EventHandler.cpp EventHandler.h
		$(CXX) $(CXXFLAGS) -c EventHandler.cpp

Game.o: Game.cpp actor/Enemy.h
		$(CXX) $(CXXFLAGS) -c Game.cpp
				
Maze.o: Maze.cpp
		$(CXX) $(CXXFLAGS) -c Maze.cpp
				
Tile.o: Tile.cpp EventHandler.h
		$(CXX) $(CXXFLAGS) -c Tile.cpp
