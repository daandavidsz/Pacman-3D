CXX=g++
CXXFLAGS=-Wall -Wno-unused-parameter -Wno-switch -lglut -lGLU -lGL `Magick++-config --cppflags --cxxflags --ldflags --libs`

all: Pacman

Pacman: Pacman.o EventHandler.o Actor.o Enemy.o Player.o Blinky.o Inky.o Pinky.o Clyde.o Maze.o Game.o Tile.o
		$(CXX) $(CXXFLAGS) Pacman.o EventHandler.o Actor.o Enemy.o Player.o Blinky.o Inky.o Pinky.o Clyde.o Maze.o Game.o Tile.o -o Pacman

Pacman.o: Pacman.cpp Renderer.cpp
		$(CXX) $(CXXFLAGS) -c Pacman.cpp
		
Actor.o: actor/Actor.cpp actor/Actor.h
		$(CXX) $(CXXFLAGS) -c actor/Actor.cpp

Player.o: actor/Player.cpp actor/Player.h
		$(CXX) $(CXXFLAGS) -c actor/Player.cpp
		
Enemy.o: actor/Enemy.cpp actor/Enemy.h
		$(CXX) $(CXXFLAGS) -c actor/Enemy.cpp	
		
Blinky.o: actor/Blinky.cpp actor/Blinky.h
		$(CXX) $(CXXFLAGS) -c actor/Blinky.cpp
		
Inky.o: actor/Inky.cpp actor/Inky.h
		$(CXX) $(CXXFLAGS) -c actor/Inky.cpp		
		
Pinky.o: actor/Pinky.cpp actor/Pinky.h
		$(CXX) $(CXXFLAGS) -c actor/Pinky.cpp

Clyde.o: actor/Clyde.cpp actor/Clyde.h
		$(CXX) $(CXXFLAGS) -c actor/Clyde.cpp
		
EventHandler.o: EventHandler.cpp EventHandler.h
		$(CXX) $(CXXFLAGS) -c EventHandler.cpp

Game.o: Game.cpp Game.h
		$(CXX) $(CXXFLAGS) -c Game.cpp
				
Maze.o: Maze.cpp Maze.h
		$(CXX) $(CXXFLAGS) -c Maze.cpp
				
Tile.o: Tile.cpp Tile.h
		$(CXX) $(CXXFLAGS) -c Tile.cpp
