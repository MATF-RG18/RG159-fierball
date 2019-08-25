#include "Player.h"

void Player::Reset()
{
    switch (_playerNumber)
    {
        case 1:
            _xPos = -PlayerInitialXPosition;
            break;
        case 2:
            _xPos = +PlayerInitialXPosition;
            break;
    }
    _yPos = PlayerInitialYPosition;
    _zPos = 0;
    _playerJumpState = playerJumpState::GROUND;
}

void Player::drawPlayer() 
{
    //iscrtavanje celog igraca
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
        glTranslatef(0, -100.0, 0); //telo je za -100 ispod glave po y osi
        glutSolidCube(90);
    glPopMatrix();
}

void Player::drawHead() 
{
    glPushMatrix();
        glColor3f(255, 255, 0);
        glColor3f(255, 255, 0);
        glutSolidSphere(PlayerHeadSize, 50, 50);
    glPopMatrix();
}

void Player::PlayerJumpUpdate()
{
    //ako ne skace izlazimo
    if(_playerJumpState == playerJumpState::GROUND)
        return;
    
    //ako je u skoku ka gore a jos nije dostigao max
    if(_playerJumpState == playerJumpState::UP)
    {
        _yPos+=10;
    }
    
    //ako je dostigao max i krenuo ka dole
    if(_playerJumpState == playerJumpState::DOWN)
    {
        _yPos-=15;
    }
    
    //dostigao max
    if(_yPos >= PlayerMaxJumpYHeight)
    {
        _playerJumpState = playerJumpState::DOWN;
    }
    
    //zavrsio skok
    if(_yPos < PlayerInitialYPosition)
    {
        _playerJumpState = playerJumpState::GROUND;
        _yPos = PlayerInitialYPosition;
    }
}
