#include "Player.h"

void Player::drawPlayer() 
{
    glPushMatrix();
        glTranslatef(_xPos, _yPos, _zPos);
        drawHead();
        drawBody();
    glPopMatrix();
}

void Player::drawBody() 
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
void Player::drawHead() 
{
        /*//sa neta uzeo boju zlata
    GLfloat ambijentMaterijala[] = {0.24725, 0.1995, 0.0745, 1.0 };
    GLfloat difuznoMaterijala[] = {0.75164, 0.60648, 0.22648, 1.0 };
    GLfloat spekularnoMaterijala[] = {0.628281, 0.555802, 0.366065, 1.0 };
    GLfloat emisionoMaterijala[] = {0, 0, 0, 0};
    GLfloat sajnes = 51.2;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambijentMaterijala);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, difuznoMaterijala);
    glMaterialfv(GL_FRONT, GL_SPECULAR, spekularnoMaterijala);
    glMaterialf(GL_FRONT, GL_SHININESS, sajnes);
    glMaterialfv(GL_FRONT, GL_EMISSION, emisionoMaterijala);*/
    
    glPushMatrix();
        glColor3f(255, 255, 0);
        glColor3f(dvapet, dvapet, 0);
        glutSolidSphere(50.0, 50, 50);

    glPopMatrix();
}

void Player::PlayerJumpUpdate()
{
    if(_playerJumpState == playerJumpState::GROUND)
        return;
    
    if(_playerJumpState == playerJumpState::UP)
    {
        _yPos+=10;
    }
    
    if(_playerJumpState == playerJumpState::DOWN)
    {
        _yPos-=15;
    }
    
    if(_yPos >= 100.0)
    {
        _playerJumpState = playerJumpState::DOWN;
    }
    
    if(_yPos < -60.0)
    {
        _playerJumpState = playerJumpState::GROUND;
        _yPos = -60.0;
    }
}
