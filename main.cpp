#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <vector>
#include "Player.h"
#include "Playground.h"
#include "Ball.h"
#include "Game.h"
#include "Fan.h"

/*Funkcije za ispis teksta na ekranu*/
static void WriteStartScreen(void);
static void WriteEndScreen(char* winner);
static void WritePoints(void);
static void WriteInstructions(void);
static void WriteGoalScored();
static void ConvertIntToChar(int x, char *s);

/* Vreme proteklo od pocetka simulacije. */
static float hours;

/* Fleg koji odredjuje stanje tajmera. */
static int timer_active;

/*Tajmer za trajanje simulacije kod postignutog gola*/
static int goal_timer = 101;

/*Tekst koji ce pisati za pobednika*/
char* winnerText;

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

//fanovi
std::vector<Fan> playerOneFans;
std::vector<Fan> playerTwoFans;

static Player playerFan = Player(1);

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
    
    //inicijalizacija fanova 
    int i, j;
    for(j=0; j<3; j++)
        for(i=0; i<=6; i++)
        {
            Fan fan = Fan(1, j);
            fan.setXPos(fan.getXPos() + i * X_DistanceBeetwenFans );
            playerOneFans.push_back(fan);
        }
    for(j=0; j<3; j++)
        for(i=0; i<=6; i++)
        {
            Fan fan = Fan(2, j);
            fan.setXPos(fan.getXPos() + i * X_DistanceBeetwenFans );
            playerTwoFans.push_back(fan);
        }
        
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
            game.SetGameState(gameState::GAME_PLAYING);
            glutTimerFunc(20, on_timer, 0);
            timer_active = 1;
        }
        break;

    case 's':
    case 'S':
        /* Zaustavlja se simulacija. */
        timer_active = 0;
        break;
    //pomeranje prvog igraca
    case 'd':
    case 'D':
        if(playerOne.getXPos()<=PlayerFieldBorder)
            playerOne.setXPos(playerOne.getXPos() + PlayerOnKeyboardMovement);
        break;
    case 'a':
    case 'A':
        if(playerOne.getXPos()>=-PlayerFieldBorder)
            playerOne.setXPos(playerOne.getXPos() - PlayerOnKeyboardMovement);
        break;

    //pomeranje drugog igraca
    case 'l':
    case 'L':
        if (playerTwo.getXPos() <= PlayerFieldBorder)
            playerTwo.setXPos(playerTwo.getXPos() + PlayerOnKeyboardMovement);
        break;
    case 'j':
    case 'J':
        if (playerOne.getXPos() >= -PlayerFieldBorder)
            playerTwo.setXPos(playerTwo.getXPos() - PlayerOnKeyboardMovement);
        break;
    //skok prvog igraca
    case 'w':
    case 'W':
        if(playerOne.getPlayerJumpState() == playerJumpState::GROUND)
        {
            playerOne.setPlayerJumpState(playerJumpState::UP);
        }
        break;
    //skok drugog igraca
    case 'i':
    case 'I':
        if(playerTwo.getPlayerJumpState() == playerJumpState::GROUND)
        {
            playerTwo.setPlayerJumpState(playerJumpState::UP);
        }
        break;
    default:
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
    
    //azuriranje pozicija objekata ako je igra u toku
    if(game.GetGameState() == gameState::GAME_PLAYING)
    {
        ball.CheckHeadCollision(playerOne.getXPos(), playerOne.getYPos());
        ball.CheckHeadCollision(playerTwo.getXPos(), playerTwo.getYPos());
        ball.CheckBodyCollision(playerOne.getXPos(), playerOne.getYPos());
        ball.CheckBodyCollision(playerTwo.getXPos(), playerTwo.getYPos());
        //usporavanje lopte ako je postignut gol
        if(goal_timer < 101 && goal_timer > 0)
        {
            ball.setXSpeed(6.0);
            ball.setYSpeed(-12.1);
        }
        ball.Update();
        //skok igraca
        playerOne.PlayerJumpUpdate();
        playerTwo.PlayerJumpUpdate();
    };
    
    //igrac A (1) je pobedio
    if(game.GetPlayerAScore() == 3 && goal_timer == 0)
    {
        game.SetGameState(gameState::GAME_END);
        game.SetPlayerAScore(0);
        game.SetPlayerBScore(0);
        timer_active = 0;
        winnerText = (char *)"PLAYER 1 WINS";
    };
    
    //igrac B (2) je pobedio
    if(game.GetPlayerBScore() == 3 && goal_timer == 0)
    {
        game.SetGameState(gameState::GAME_END);
        game.SetPlayerAScore(0);
        game.SetPlayerBScore(0);
        timer_active = 0;
        winnerText = (char *)"PLAYER 2 WINS";
    };
    
    //resetovanje na pocetne pozicije ako je gol postignut
    if(goal_timer == 0)
    {
        goal_timer = 101;
        ball.Reset();
        playerOne.Reset();
        playerTwo.Reset();
        
        int i;
        for(i=0; i<21; i++)
        {
            playerOneFans[i].Reset();
        }
        
        for(i=0; i<21; i++)
        {
            playerTwoFans[i].Reset();
        }
        ball.setPlayerAGoal(false);
        ball.setPlayerBGoal(false);
    }
    
    //pokretanje slavlja ako je igrac A(1) postigao gol
    if(ball.getPlayerAGoal() == true && goal_timer == 101)
    {
        goal_timer = 100;
        game.IncreasePlayerAScore();
    }
    
    //pokretanje slavlja ako je igrac B(2) postigao gol
    if(ball.getPlayerBGoal() == true && goal_timer == 101)
    {
        goal_timer = 100;
        game.IncreasePlayerBScore();
    }
    
    //radovanje navijaca
    if(ball.getPlayerAGoal() == true && goal_timer < 100 && goal_timer > 0)
    {
        int i;
        for(i=0; i<21; i++)
        {
            if( playerOneFans[i].getFanJumpState() == playerJumpState::GROUND )
                playerOneFans[i].setFanJumpState(playerJumpState::UP);
            playerOneFans[i].FanJumpUpdate();
        }
    }
    
    //radovanje navijaca
    if(ball.getPlayerBGoal() == true && goal_timer < 100 && goal_timer > 0)
    {
        int i;
        for(i=0; i<21; i++)
        {
            if( playerTwoFans[i].getFanJumpState() == playerJumpState::GROUND )
                playerTwoFans[i].setFanJumpState(playerJumpState::UP);
            playerTwoFans[i].FanJumpUpdate();
        }
    }

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
    gluPerspective(60, (float)width / height, 1, 2000);
}

static void on_display(void)
{
    /*boja pozadine*/
    glClearColor(0, 0.72,0.96,0);
    
    /* Pozicija svetla. */
    GLfloat light_position[] = {1, 1, 1, 0};

    /* Ambijentalna boja svetla. */
    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1 };

    /* Difuzna boja svetla. */
    GLfloat light_diffuse[] = { 1, 1, 1, 1 };

    /* Spekularna boja svetla. */
    GLfloat light_specular[] = {  1, 1, 1, 1 };

    /* Koeficijenti spekularne refleksije materijala. */
    GLfloat specular_coeffs[] = { 1, 1, 1, 1 };

    /* Koeficijent glatkosti materijala. */
    GLfloat shininess = 20;
    
    /* Postavlja se boja svih piksela na zadatu boju pozadine. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /* Postavlja se vidna tacka. */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 1000, 0, 0, 0, 0, 1, 0);
    
    /* Ukljucuje se osvjetljenje i podesavaju parametri svetla. */
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    /* Podesavaju se parametri materijala. */
    glEnable ( GL_COLOR_MATERIAL ) ;
    glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

    //iscrtavanje u slucaju da traje igra
    if(game.GetGameState() == gameState::GAME_PLAYING)
    {    
        playground.drawField();
        playerOne.drawPlayer();
        playerTwo.drawPlayer();
        ball.drawBall();
        WritePoints();
        WriteInstructions();
        
        int i;
        for(i=0; i<21; i++)
        {
            playerOneFans[i].drawFan();
        }
        
        for(i=0; i<21; i++)
        {
            playerTwoFans[i].drawFan();
        }
    };
    
    //iscrtavanje i azuriranje za vreme proslave gola
    if(goal_timer > 0 && goal_timer <= 100)
    {
        WriteGoalScored();
        goal_timer--;
    }
    
    //pocetni ekran
    if(game.GetGameState() == gameState::GAME_START)
    {
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        WriteStartScreen();
    };
    
    //zavrsni ekran
    if(game.GetGameState() == gameState::GAME_END)
    {
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        WriteEndScreen(winnerText);
    };
    

    /* Postavlja se nova slika u prozor. */
    glutSwapBuffers();
}

static void WriteStartScreen(void)
{
    glDisable(GL_LIGHTING);
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
    
	glEnable(GL_LIGHTING);
}

static void WriteEndScreen(char* winner)
{
    glDisable(GL_LIGHTING);
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
    
	glEnable(GL_LIGHTING);
}

static void WriteGoalScored()
{
    glDisable(GL_LIGHTING);
	glColor3f(1, 1, 1);    
    int i;
    
    glRasterPos3f(StartScreenXPosition, StartScreenYPositionLine_1 + 50, StartScreenZPosition);
    char s[] = "GOOOOOOOOAAAAAAAAALLL";
    for(i = 0; s[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
    
	glEnable(GL_LIGHTING);
}

static void WriteInstructions()
{
    glDisable(GL_LIGHTING);
	glColor3f(1, 1, 1);    
    int i;
    
    glRasterPos3f(-600, PlayerAPointsY, PlayerAPointsZ);
    char s[] = "A-Left D-Right W-Jump ";
    for(i = 0; s[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
    
    glRasterPos3f(200, PlayerAPointsY, PlayerAPointsZ);
    char p[] = "J-Left L-Right I-Jump ";
    for(i = 0; p[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, p[i]);
    
	glEnable(GL_LIGHTING);
}

static void WritePoints(void)
{
    glDisable(GL_LIGHTING);
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
    
	glEnable(GL_LIGHTING);
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
    return;
    
}
