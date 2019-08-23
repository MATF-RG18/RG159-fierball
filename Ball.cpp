#include "Ball.h"
#include <stdio.h>
#include <math.h>
#include "Helpers.h"

void Ball::drawBall() 
{
    glEnable(GL_LIGHTING);
        //sa neta uzeo boju zlata
    GLfloat ambijentMaterijala[] = {1.0, 1.0, 1.0, 1.0 };
    GLfloat difuznoMaterijala[] = {0.75164, 0.60648, 0.22648, 1.0 };
    GLfloat spekularnoMaterijala[] = {0.628281, 0.555802, 0.366065, 1.0 };
    GLfloat emisionoMaterijala[] = {0, 0, 0, 0};
    GLfloat sajnes = 51.2;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambijentMaterijala);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, difuznoMaterijala);
    glMaterialfv(GL_FRONT, GL_SPECULAR, spekularnoMaterijala);
    glMaterialf(GL_FRONT, GL_SHININESS, sajnes);
    glMaterialfv(GL_FRONT, GL_EMISSION, emisionoMaterijala);
    
    glPushMatrix();
        //glColor3f(1, 1, 1);
        glTranslatef(_xPos, _yPos, _zPos);
        glutSolidSphere(50.0, 50, 50);
    glPopMatrix();
    glDisable(GL_LIGHTING);
}

void Ball::Update()
{   
    //Kod preuzet donekle sa casova vezbi, adaptiran za moj slucaj
    if(_xSpeed > 0)
    {
        _xPos += _xSpeed*_xDirection;
        if (_xPos <= -(600 + BallSize / 2)) {
            if(_yPos > -200 && _yPos < 100)
            {
                _PlayerBGoal = true;
            }
            _xDirection *= -1;
            _xPos = -(600 + BallSize / 2);
        }
        if (_xPos >= 600 + BallSize / 2) 
        {
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

    if (_yPos >= 400 - BallSize / 2) {
        _ySpeed *= -1;
        _yPos = 400 - BallSize / 2;
    }

    _xSpeed -= 0.06;
    _ySpeed -= 5.0;
}

void Ball::CheckHeadCollision(float x, float y)
{
    float distance = sqrt((_xPos - x)*(_xPos - x) + (_yPos - y)*(_yPos - y));
    if(distance <= BallSize*2)
    {
        _xDirection *= -1;
        _xSpeed = 25.0;
        //_ySpeed *= -1;
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
    //telo je za 100 ispod glave po y osi
    y-=100;
    
    float distance = sqrt((_xPos - x)*(_xPos - x) + (_yPos - y)*(_yPos - y));
    //racunam koliziju sa unutrasnjim upisanim krugom kvadrata
    if(distance <= (BallSize + PlayerBodySize/2))
    {
        _xDirection *= -1;
        _xSpeed = 30.0;
        _ySpeed = 48.1;
        //_ySpeed *= -1;
        /*if(_ySpeed > 0)
        {
            _ySpeed = -12.1;
        };
        if(_ySpeed < 0)
        {
            _ySpeed = 12.1;
        };*/
    }    
}
