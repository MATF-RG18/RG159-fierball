program: main.cpp Player.cpp Playground.cpp
	g++ $^ -o $@ -lGL -lGLU -lglut -lm
