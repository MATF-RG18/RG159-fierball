program: main.cpp Player.cpp Playground.cpp Ball.cpp Game.cpp Helpers.h Fan.cpp
	g++ $^ -o $@ -lGL -lGLU -lglut -lm
