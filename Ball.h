#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#pragma once
class Ball
{
public:
    Ball()
    {
        _xPos = 0.0;
        _yPos = 300.0;
        _zPos = 0.0;
        //_ySpeed = -1.0;
        _ySpeed = 13.0;
        _yMax = 300;
        _direction = -1;
        _dropMaxRate = 0.4;
    };
    
    void drawBall();
    void Update();
    
    //getters and setters
    float getXPos() { return _xPos; } 
    void setXPos(float x) { _xPos = x; }
    float getYPos() { return _yPos; }
    void setYPos(float y) { _yPos = y; }
    float getZPos() { return _zPos; }
    void setZPos(float z) { _zPos = z; }
private:
    float _xPos;
    float _yPos;
    float _zPos;
    
    float _xSpeed;
    float _ySpeed;
    
    float _yMax;
    int _direction;
    
    float _dropMaxRate;
};

