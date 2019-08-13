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
    glPushMatrix();
        glColor3f(255, 255, 0);
        glutSolidSphere(50.0, 50, 50);

    glPopMatrix();
}

void Player::drawEyebrows() 
{

}