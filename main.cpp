#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "Player.h"
#include "Playground.h"

/* Vreme proteklo od pocetka simulacije. */
static float hours;

/* Fleg koji odredjuje stanje tajmera. */
static int timer_active;

/* Deklaracije callback funkcija. */
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_timer(int value);
static void on_display(void);

static Player playerOne = Player(1);
static Player playerTwo = Player(2);
static Playground playground = Playground();

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);

    hours = 0;
    timer_active = 0;

    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();

    return 0;
}

static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        /* Zavrsava se program. */
        exit(0);
        break;

    case 'g':
    case 'G':
        /* Pokrece se simulacija. */
        if (!timer_active) {
            glutTimerFunc(50, on_timer, 0);
            timer_active = 1;
        }
        break;

    case 's':
    case 'S':
        /* Zaustavlja se simulacija. */
        timer_active = 0;
        break;
    //player ONE movement
    case 'd':
    case 'D':
        if(playerOne.getXPos()<=595.0)
            playerOne.setXPos(playerOne.getXPos() + 5.0);
        break;
    case 'a':
    case 'A':
        if(playerOne.getXPos()>=-595.0)
            playerOne.setXPos(playerOne.getXPos() - 5.0);
        break;

    //player TWO movement
    case 'l':
    case 'L':
        if (playerTwo.getXPos() <= 595.0)
            playerTwo.setXPos(playerTwo.getXPos() + 5.0);
        break;
    case 'j':
    case 'J':
        if (playerOne.getXPos() >= -595.0)
            playerTwo.setXPos(playerTwo.getXPos() - 5.0);
        break;
    }
}



static void on_timer(int value)
{
    /* Proverava se da li callback dolazi od odgovarajuceg tajmera. */
    if (value != 0)
        return;

    /* Azurira se vreme simulacije. */
    hours += 18;

    /* Forsira se ponovno iscrtavanje prozora. */
    glutPostRedisplay();

    /* Po potrebi se ponovo postavlja tajmer. */
    if (timer_active)
        glutTimerFunc(50, on_timer, 0);
}

static void on_reshape(int width, int height)
{
    /* Postavlja se viewport. */
    glViewport(0, 0, width, height);

    /* Postavljaju se parametri projekcije. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)width / height, 1, 1500);
}

static void on_display(void)
{
    /* Postavlja se boja svih piksela na zadatu boju pozadine. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Postavlja se vidna tacka. */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 1000, 0, 0, 0, 0, 1, 0);

    playground.drawField();
    playerOne.drawPlayer();
    playerTwo.drawPlayer();

    /* Odredjuje se ugao rotacije Sunca i generise se ovo telo. 
    sun_rotation = 360 * hours / (15 * 24);
    glPushMatrix();
    glRotatef(sun_rotation, 0, 0, 1);
    glColor3f(1, 1, 0);
    glutWireSphere(50, 10, 10);
    glPopMatrix();

    /* Odredjuju se uglovi rotacije Zemlje i generise se ovo telo. 
    earth_revolution = 360 * hours / (365 * 24);
    earth_rotation = 360 * hours / (1 * 24);

    glRotatef(earth_revolution, 0, 0, 1);
    glTranslatef(300, 0, 0);

    glPushMatrix();
    glRotatef(earth_rotation, 0, 0, 1);
    glColor3f(0, 0, 1);
    glutWireSphere(20, 10, 10);
    glPopMatrix();

    /* Odredjuju se uglovi rotacije Meseca i
    * generise se ovo telo. 
    moon_revolution = 360 * hours / (28 * 24);
    moon_rotation = 360 * hours / (28 * 24);

    glRotatef(moon_revolution, 0, 0, 1);
    glTranslatef(100, 0, 0);
    glRotatef(moon_rotation, 0, 0, 1);
    glColor3f(1, 1, 1);
    glutWireSphere(10, 10, 10); */

    /* Postavlja se nova slika u prozor. */
    glutSwapBuffers();
}
