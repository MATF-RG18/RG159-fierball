#include "Ball.h"
#include <stdio.h>

static float size = 25.0;

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
    if(_yMax <= 0.0005)
    {
        return;
    }
    int a;
    _yPos += _direction*_ySpeed;
    if (_yPos <= -(200 - size)) {
        _direction *= -1;
        _yPos = -(200 - size);
        _yMax = _yMax*_dropMaxRate;
        _dropMaxRate*=0.50;
    }

    if (_yPos >= _yMax) {
        printf("%f >= %f \n", _yPos, _yMax);
        _direction *= -1;
        _yPos = _yMax;        
    }

    //_ySpeed -= 0.01;
    _ySpeed*=0.996;
}
