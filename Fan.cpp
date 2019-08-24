#include "Fan.h"

void Fan::drawFan() 
{
    glPushMatrix();
        glTranslatef(_xPos, _yPos, _zPos);
        drawHead();
        drawBody();
    glPopMatrix();
}

void Fan::drawBody() 
{
    glPushMatrix();
        if(_playerNumber == 1)
            glColor3f(1, 0, 0);
        if (_playerNumber == 2)
            glColor3f(0, 0, 1);
        glTranslatef(0, -100.0, 0);
        glutSolidCube(90);
    glPopMatrix();
}

//head drawing functions
void Fan::drawHead() 
{
    glPushMatrix();
        glColor3f(255, 255, 0);
        glColor3f(dvapet, dvapet, 0);
        glutSolidSphere(50.0, 50, 50);

    glPopMatrix();
}

void Fan::FanJumpUpdate()
{
    if(_fanJumpState == playerJumpState::GROUND)
        return;
    
    if(_fanJumpState == playerJumpState::UP)
    {
        _yPos+=10;
    }
    
    if(_fanJumpState == playerJumpState::DOWN)
    {
        _yPos-=15;
    }
    
    if(_yPos >= 240.0)
    {
        _fanJumpState = playerJumpState::DOWN;
    }
    
    if(_yPos < 100.0)
    {
        _fanJumpState = playerJumpState::GROUND;
        _yPos = 100.0;
    }
}
