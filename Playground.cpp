#include "Playground.h"
#include "Helpers.h"

void Playground::drawField(GLuint names[])
{
    glPushMatrix();
        glTranslatef(0, -200.0, 0);
        glRotatef(-70, 1, 0, 0);
        drawGrass(names);
        drawLines();
        drawGoals();
    glPopMatrix();
}

void Playground::drawGrass(GLuint names[]) 
{
    glBindTexture(GL_TEXTURE_2D, names[1]);
    //Iscrtavanje zelene povrsine
    const float xCor = 1400.0, yCorFar = 350.0, yCorNear = 450.0, zCor = 0;
    glPushMatrix();
        glColor3f(0, 1, 0);
        glBegin(GL_QUADS);
            glTexCoord2f(0, 0);
            glVertex3f(-xCor, -yCorNear, zCor);
            glTexCoord2f(10, 0);
            glVertex3f(xCor, -yCorNear, zCor);
            glTexCoord2f(10, 10);
            glVertex3f(xCor, yCorFar, zCor);
            glTexCoord2f(0, 10);
            glVertex3f(-xCor, yCorFar, zCor);
        glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Playground::drawLines() 
{
    glDisable(GL_LIGHTING);
    const float xCor = 600.0, yCor = 260.0, zCor = 0.5;
    const float xCor16 = 400.0, yCor16 = 190.0;
    glPushMatrix();
        glColor3f(1, 1, 1);
        glLineWidth(8);

        glBegin(GL_LINES);
        //linije koje ogranicavaju teren
            glVertex3f(-xCor, -yCor, zCor);
            glVertex3f(xCor, -yCor, zCor);

            glVertex3f(xCor, -yCor, zCor);
            glVertex3f(xCor, yCor, zCor);

            glVertex3f(xCor, yCor, zCor);
            glVertex3f(-xCor, yCor, zCor);

            glVertex3f(-xCor, yCor, zCor);
            glVertex3f(-xCor, -yCor, zCor);
        //centralna linija
            glVertex3f(0, yCor, zCor);
            glVertex3f(0, -yCor, zCor);
        //"16m" sa leve strane
            glVertex3f(-xCor, -yCor16, zCor);
            glVertex3f(-xCor16, -yCor16, zCor);

            glVertex3f(-xCor16, -yCor16, zCor);
            glVertex3f(-xCor16, yCor16, zCor);

            glVertex3f(-xCor16, yCor16, zCor);
            glVertex3f(-xCor, yCor16, zCor);
        //"16m" sa desne strane
            glVertex3f(xCor, -yCor16, zCor);
            glVertex3f(xCor16, -yCor16, zCor);

            glVertex3f(xCor16, -yCor16, zCor);
            glVertex3f(xCor16, yCor16, zCor);

            glVertex3f(xCor16, yCor16, zCor);
            glVertex3f(xCor, yCor16, zCor);
        glEnd();

        //centralna kruznica
        float r = 100.0, cx = 0, cy = 0;
        float theta, xHelp, yHelp;
        glBegin(GL_LINE_LOOP);
        for (int ii = 0; ii < 100; ii++) {
            theta = 2.0f * PI * float(ii) / float(100);
            xHelp = r * cosf(theta);
            yHelp = r * sinf(theta);
            glVertex3f(xHelp + cx, yHelp + cy, zCor);
        }
        glEnd();
        //polukrug kod levog "16m"
        glPushMatrix();
        glTranslatef(-xCor16, 0, 0);
        glRotatef(-90, 0, 0, 1);
        r = 100.0, cx = 0, cy = 0;
        glBegin(GL_LINE_LOOP);
        for (int ii = 0; ii < 100; ii++) {
            theta = 2.0f * (PI/2) * float(ii) / float(100);
            xHelp = r * cosf(theta);
            yHelp = r * sinf(theta);
            glVertex3f(xHelp + cx, yHelp + cy, zCor);
        }
        glEnd();
        glPopMatrix();
        //polukrug kod desnog "16m"
        glPushMatrix();
        glTranslatef(xCor16, 0, 0);
        glRotatef(90, 0, 0, 1);
        r = 100.0, cx = 0, cy = 0;
        glBegin(GL_LINE_LOOP);
        for (int ii = 0; ii < 100; ii++) {
            theta = 2.0f * (PI / 2) * float(ii) / float(100);
            xHelp = r * cosf(theta);
            yHelp = r * sinf(theta);
            glVertex3f(xHelp + cx, yHelp + cy, zCor);
        }
        glEnd();
        glPopMatrix();

    glPopMatrix();
    
    glEnable(GL_LIGHTING);
}

void Playground::drawGoals() 
{
    float crossBarHeight = 200;
    float barHeight = 300;
    float goalHolderHeight = 330;
    float cylinderWidth = 8;
    float goalHolderRotation = 27;
    //levi gol
    glPushMatrix();

    glTranslatef(-600, 0, 0);
        glPushMatrix();
        glRotatef(90, 0, 0, 1);
        //bliza stativa
        glPushMatrix();
            glTranslatef(-100, 0, 0);
            glColor3f(1, 1, 1);
            GLUquadric* quad = gluNewQuadric();
            gluCylinder(quad, cylinderWidth, cylinderWidth, barHeight, 50, 50);
        glPopMatrix();

        //dalja stativa
        glPushMatrix();
            glTranslatef(100, 0, 0);
            glColor3f(1, 1, 1);
            quad = gluNewQuadric();
            gluCylinder(quad, cylinderWidth, cylinderWidth, barHeight, 50, 50);
        glPopMatrix();

        //precka
        glPushMatrix();
            glTranslatef(-100, 0, 300);
            glRotatef(90, 0, 1, 0);
            glColor3f(1, 1, 1);
            quad = gluNewQuadric();
            gluCylinder(quad, cylinderWidth, cylinderWidth, crossBarHeight, 50, 50);
        glPopMatrix();
        
        //blizi drzac gola
        glPushMatrix();
            glTranslatef(-100, 150, 0);
            glColor3f(1, 1, 1);
            quad = gluNewQuadric();
            glRotatef(goalHolderRotation, 1, 0, 0);
            gluCylinder(quad, cylinderWidth, cylinderWidth, goalHolderHeight, 50, 50);
        glPopMatrix();
        
        //dalji drzac gola
        glPushMatrix();
            glTranslatef(100, 150, 0);
            glColor3f(1, 1, 1);
            quad = gluNewQuadric();
            glRotatef(goalHolderRotation, 1, 0, 0);
            gluCylinder(quad, cylinderWidth, cylinderWidth, goalHolderHeight, 50, 50);
        glPopMatrix();
        
        glPopMatrix();

    glPopMatrix();

    //desni gol
    glPushMatrix();

    glTranslatef(600, 0, 0);
    glPushMatrix();
        glRotatef(90, 0, 0, 1);
        //bliza stativa
        glPushMatrix();
            glTranslatef(-100, 0, 0);
            glColor3f(1, 1, 1);
            quad = gluNewQuadric();
            gluCylinder(quad, cylinderWidth, cylinderWidth, barHeight, 50, 50);
        glPopMatrix();

        //dalja stativa
        glPushMatrix();
            glTranslatef(100, 0, 0);
            glColor3f(1, 1, 1);
            quad = gluNewQuadric();
            gluCylinder(quad, cylinderWidth, cylinderWidth, barHeight, 50, 50);
        glPopMatrix();

        //precka
        glPushMatrix();
            glTranslatef(-100, 0, 300);
            glRotatef(90, 0, 1, 0);
            glColor3f(1, 1, 1);
            quad = gluNewQuadric();
            gluCylinder(quad, cylinderWidth, cylinderWidth, crossBarHeight, 50, 50);
        glPopMatrix();
        
        //blizi drzac gola
        glPushMatrix();
            glTranslatef(-100, -150, 0);
            glColor3f(1, 1, 1);
            quad = gluNewQuadric();
            glRotatef(-goalHolderRotation, 1, 0, 0);
            gluCylinder(quad, cylinderWidth, cylinderWidth, goalHolderHeight, 50, 50); //bliza
        glPopMatrix();
        
        //dalji drzac gola
        glPushMatrix();
            glTranslatef(100, -150, 0);
            glColor3f(1, 1, 1);
            quad = gluNewQuadric();
            glRotatef(-goalHolderRotation, 1, 0, 0);
            gluCylinder(quad, cylinderWidth, cylinderWidth, goalHolderHeight, 50, 50); //dalja
        glPopMatrix();
        
    glPopMatrix();

    glPopMatrix();
}
