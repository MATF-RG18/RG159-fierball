#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#pragma once
class Playground
{
public:
    Playground() {};

    void drawField(GLuint names[]);
    void drawGrass(GLuint names[]);
    void drawLines();
    void drawGoals();
};

