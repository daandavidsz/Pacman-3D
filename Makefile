CXX=g++
CXXFLAGS=-Wall -Wno-unused-parameter -Wno-switch -lglut -lGLU -lGL `Magick++-config --cppflags --cxxflags --ldflags --libs`

all: Pacman

Pacman: Pacman.o EventHandler.o Actor.o Enemy.o Player.o Blinky.o Inky.o Pinky.o Clyde.o Bonus.o Cherry.o Maze.o Game.o Tile.o ScoreBoard.o PacmanExplosion.o
		$(CXX) $(CXXFLAGS) Pacman.o EventHandler.o Actor.o Enemy.o Player.o Blinky.o Inky.o Pinky.o Clyde.o Bonus.o Cherry.o Maze.o Game.o Tile.o ScoreBoard.o PacmanExplosion.o -o Pacman

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
		
Bonus.o: bonus/Bonus.cpp bonus/Bonus.h
		$(CXX) $(CXXFLAGS) -c bonus/Bonus.cpp
		
Cherry.o: bonus/Cherry.cpp bonus/Cherry.h
		$(CXX) $(CXXFLAGS) -c bonus/Cherry.cpp

PacmanExplosion.o: object/PacmanExplosion.cpp object/PacmanExplosion.h object/Particle.h object/Particle.cpp object/Vector.h
		$(CXX) $(CXXFLAGS) -c object/PacmanExplosion.cpp
		
ScoreBoard.o: object/ScoreBoard.cpp object/ScoreBoard.h
		$(CXX) $(CXXFLAGS) -c object/ScoreBoard.cpp
		
EventHandler.o: EventHandler.cpp EventHandler.h
		$(CXX) $(CXXFLAGS) -c EventHandler.cpp

Game.o: Game.cpp Game.h
		$(CXX) $(CXXFLAGS) -c Game.cpp
				
Maze.o: Maze.cpp Maze.h Direction.h
		$(CXX) $(CXXFLAGS) -c Maze.cpp
				
Tile.o: Tile.cpp Tile.h
		$(CXX) $(CXXFLAGS) -c Tile.cpp
