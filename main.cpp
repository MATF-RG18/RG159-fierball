#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "Player.h"
#include "Playground.h"
#include "Ball.h"
#include "Game.h"

static int trying = 0;

/*Screen Writing*/
static void WriteStartScreen(void);
static void WriteEndScreen(char* winner);
static void WritePoints(void);
static void ConvertIntToChar(int x, char *s);
static void RevertString(char *s, int n);

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
static Ball ball = Ball();
static Game game = Game();

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
    //glEnable(GL_LIGHTING);

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
            game.SetGameState(gameState::GAME_PLAYING);
            //reset everything TODO
            glutTimerFunc(20, on_timer, 0);
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
    
    if(game.GetGameState() == gameState::GAME_PLAYING)
    {
        ball.Update();
    };
    
    if(game.GetGameState() == gameState::GAME_PLAYING)
    {
    trying++;
    
    if(trying %100 == 0)
    {
        game.IncreasePlayerAScore();
    }
    }
    
    if(game.GetPlayerAScore() >= 3)
    {
        game.SetGameState(gameState::GAME_END);
        game.SetPlayerAScore(0);
        timer_active = 0;
    };

    /* Forsira se ponovno iscrtavanje prozora. */
    glutPostRedisplay();

    /* Po potrebi se ponovo postavlja tajmer. */
    if (timer_active)
        glutTimerFunc(20, on_timer, 0);
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
    
    GLfloat pozicijaSvetla[] = { 0, 1, -0.3, 0 };
    GLfloat ambijentalnoSvetlo[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat difuznoSvetlo[] = { 0.9, 0.9, 0.9, 1 };
    GLfloat spekularnoSvetlo[] = { 1, 1, 1, 1 };
    
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, pozicijaSvetla);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambijentalnoSvetlo);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difuznoSvetlo);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spekularnoSvetlo);

    /* Postavlja se vidna tacka. */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 1000, 0, 0, 0, 0, 1, 0);

    if(game.GetGameState() == gameState::GAME_PLAYING)
    {    
        playground.drawField();
        playerOne.drawPlayer();
        playerTwo.drawPlayer();
        ball.drawBall();
        WritePoints();
    };
    
    if(game.GetGameState() == gameState::GAME_START)
    {
        WriteStartScreen();
    };
    
    //trying TODO
    if(game.GetGameState() == gameState::GAME_END)
    {
        WriteEndScreen("PLAYER 1 WINS");
    };
    

    /* Postavlja se nova slika u prozor. */
    glutSwapBuffers();
}

static void WriteStartScreen(void)
{
    //glDisable(GL_LIGHTING);
    //glClearColor(0, 0, 0);
	glColor3f(1, 1, 1);
    
    int i;
    glRasterPos3f(StartScreenXPosition, StartScreenYPositionLine_2, StartScreenZPosition);
    char s[] = "PRESS 'G' TO PLAY";
    for(i = 0; s[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
    
    glRasterPos3f(StartScreenXPosition, StartScreenYPositionLine_3, StartScreenZPosition);
    char p[] = "PRESS 'ESC' TO EXIT";
    for(i = 0; p[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, p[i]);
    
	//glEnable(GL_LIGHTING);
}

static void WriteEndScreen(char* winner)
{
    //glDisable(GL_LIGHTING);
    //glClearColor(0, 0, 0);
	glColor3f(1, 1, 1);    
    int i;
    
    glRasterPos3f(StartScreenXPosition, StartScreenYPositionLine_1, StartScreenZPosition);
    for(i = 0; winner[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, winner[i]);
    
    glRasterPos3f(StartScreenXPosition, StartScreenYPositionLine_2, StartScreenZPosition);
    char s[] = "PRESS 'G' TO PLAY AGAIN";
    for(i = 0; s[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
    
    glRasterPos3f(StartScreenXPosition, StartScreenYPositionLine_3, StartScreenZPosition);
    char p[] = "PRESS 'ESC' TO EXIT";
    for(i = 0; p[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, p[i]);
    
	//glEnable(GL_LIGHTING);
}

static void WritePoints(void)
{
    //glDisable(GL_LIGHTING);
    //glClearColor(0, 0, 0);
	glColor3f(1, 1, 1);
 
    char playerA[5];
    char playerB[5];
    ConvertIntToChar(game.GetPlayerAScore(), playerA);
    ConvertIntToChar(game.GetPlayerBScore(), playerB);
    
    int i;
    
    glRasterPos3f(PlayerAPointsX, PlayerAPointsY, PlayerAPointsZ);
    for(i = 0; playerA[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, playerA[i]);
    
    glRasterPos3f(0, PlayerAPointsY, 0);
    char s[] = "-";
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[0]);
    
    glRasterPos3f(PlayerBPointsX, PlayerBPointsY, PlayerBPointsZ);
    for(i = 0; playerB[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, playerB[i]);
    
	//glEnable(GL_LIGHTING);
}

static void ConvertIntToChar(int x, char *s)
{
    if(x == 0)
    {
        s[0] = '0', s[1] = '\0';
        return;
    }
    
    int i;
    for(i = 0; x != 0; i++)
    {
        s[i] = x%10 + '0';
        x /= 10;
    }
    s[i] = '\0';
    //RevertString(s, i);
    return;
    
}

static void RevertString(char *s, int n)
{
    int i, j;
    char help;
    for(i=0, j=n-1; i<j; i++, j--)
    {
        help = s[i];
        s[i] = s[j];
        s[j] = help;
    }
}
