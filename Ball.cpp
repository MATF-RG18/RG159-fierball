#include "Ball.h"
#include <stdio.h>
#include <math.h>
#include "Helpers.h"

void Ball::drawBall() 
{
    glPushMatrix();
        glColor3f(1, 1, 1);
        glTranslatef(_xPos, _yPos, _zPos);
        glutSolidSphere(BallSize, 50, 50);
    glPopMatrix();
}

void Ball::Update()
{   
    //Kod preuzet donekle sa casova vezbi, adaptiran za moj slucaj
    if(_xSpeed > 0)
    {
        _xPos += _xSpeed*_xDirection;
        if (_xPos <= -(600 + BallSize / 2)) {
            //provera da li je igrac B dao gol
            if(_yPos > -200 && _yPos < 100)
            {
                _PlayerBGoal = true;
            }
            _xDirection *= -1;
            _xPos = -(600 + BallSize / 2);
        }
        if (_xPos >= 600 + BallSize / 2) 
        {
            //provera da li je igrac A dao gol
            if(_yPos > -200 && _yPos < 100)
            {
                _PlayerAGoal = true;
            }
            _xDirection *= -1;
            _xPos = 600 + BallSize / 2;
        }
    }

    _yPos += _ySpeed;
    if (_yPos <= -(200 - BallSize / 2)) {
        _ySpeed *= -1;
        _yPos = -(200 - BallSize / 2);
    }

    if (_yPos >= 500 - BallSize / 2) {
        _ySpeed *= -1;
        _yPos = 500 - BallSize / 2;
    }

    //podesavano po osecaju
    _xSpeed -= 0.06;
    _ySpeed -= 5.0;
}

void Ball::CheckHeadCollision(float x, float y)
{
    //provera da li je u koliziji sa igracevom glavom cije su koordinate prosledjene
    //desavanje nakon kolizije podeseno po osecaju
    float distance = sqrt((_xPos - x)*(_xPos - x) + (_yPos - y)*(_yPos - y));
    if(distance <= BallSize*2)
    {
        if(_xSpeed == 0.0)
        {
            if(x < _xPos)
                _xDirection = 1;
            else
                _xDirection = -1;
        }
        else
        {
            _xDirection *= -1;
        }
        _xSpeed = 25.0;
        
        if(_ySpeed > 0)
        {
            _ySpeed = -48.1;
        };
        if(_ySpeed < 0)
        {
            _ySpeed = 48.1;
        };
    }
}

void Ball::CheckBodyCollision(float x, float y)
{
    //provera da li je u koliziji sa igracevim telom cije su koordinate prosledjene
    //desavanje nakon kolizije podeseno po osecaju
    
    //telo je za 100 ispod glave po y osi
    y-=100;
    
    float distance = sqrt((_xPos - x)*(_xPos - x) + (_yPos - y)*(_yPos - y));
    //racunam koliziju sa unutrasnjim upisanim krugom kvadrata
    if(distance <= (BallSize + PlayerBodySize/2))
    {
        if(_xSpeed == 0.0)
        {
            if(x < _xPos)
                _xDirection = 1;
            else
                _xDirection = -1;
        }
        else
        {
            _xDirection *= -1;
        }
        _xSpeed = 30.0;
        _ySpeed = 48.1;
    }    
}
