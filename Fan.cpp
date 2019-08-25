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

void Fan::drawHead() 
{
    glPushMatrix();
        glColor3f(255, 255, 0);
        glColor3f(255, 255, 0);
        glutSolidSphere(PlayerHeadSize, 50, 50);
    glPopMatrix();
}

void Fan::FanJumpUpdate()
{
    //skakanje fanova pri radovanju je identicno uradjeno kao skok igraca, samo sa drugim parametrima
    if(_fanJumpState == playerJumpState::GROUND)
        return;
    
    if(_fanJumpState == playerJumpState::UP)
    {
        _yPos+=7;
    }
    
    if(_fanJumpState == playerJumpState::DOWN)
    {
        _yPos-=10;
    }
    
    if(_yPos >= (160.0 + _fanRow*110))
    {
        _fanJumpState = playerJumpState::DOWN;
    }
    
    if(_yPos < (70.0 + _fanRow*110))
    {
        _fanJumpState = playerJumpState::GROUND;
        _yPos = 70.0 + _fanRow*110;
    }
}

void Fan::Reset()
{
    switch (_fanRow)
    {
        case 0:
            _yPos = 70;
            break;
        case 1:
            _yPos = 180;
            break;
        case 2:
            _yPos = 290;
            break;
    }
    _fanJumpState = playerJumpState::GROUND;
}
