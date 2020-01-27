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
#include "image.h"

/*Funkcije za ispis teksta na ekranu*/
static void WriteStartScreen(void);
static void WriteEndScreen(char* winner);
static void WritePoints(void);
static void WriteInstructions(void);
static void WriteGoalScored();
static void WriteTimer(void);
static void WriteGoldenGoal(void);
static void ConvertIntToChar(int x, char *s);
static void initialize(void);

/* Imena fajlova sa teksturama. */
#define FILENAME0 "PoolWater.bmp"
#define FILENAME1 "grass.bmp"

/* Identifikatori tekstura. */
static GLuint names[2];

/* Vreme proteklo od pocetka simulacije. */
static int msecs;
static int secs;

/* Fleg koji odredjuje stanje tajmera. */
static int timer_active;

/*Tajmer za trajanje simulacije kod postignutog gola*/
static int goal_timer = 101;

/*Tekst koji ce pisati za pobednika*/
char* winnerText;

/*Kretanje igraca*/
static int playerOneLeft = 0;
static int playerOneRight = 0;
static int playerTwoLeft = 0;
static int playerTwoRight = 0;

/* Deklaracije callback funkcija. */
static void on_keyboard(unsigned char key, int x, int y);
static void on_special_keyboard(int key, int x, int y);
static void on_released_keyboard(int key, int x, int y);
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
    glutSpecialFunc(on_special_keyboard);
    glutSpecialUpFunc(on_released_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);

    msecs = MsecsDefault;
    secs = SecsDefault;
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
        
    initialize();
        
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
    default:
        break;
    }
}

static void on_special_keyboard(int key, int x, int y)
{
    if(timer_active && game.GetGameState() == gameState::GAME_PLAYING)
    {
        switch(key)
        {
            //pomeranje prvog igraca
            case GLUT_KEY_F3:
                playerOneRight = 1;
                break;
            case GLUT_KEY_F1:
                playerOneLeft = 1;
                break;

            //pomeranje drugog igraca
            case GLUT_KEY_RIGHT:
                playerTwoRight = 1;
                break;
            case GLUT_KEY_LEFT:
                playerTwoLeft = 1;
                break;
            //skok prvog igraca
            case GLUT_KEY_F2:   
                if(playerOne.getPlayerJumpState() == playerJumpState::GROUND)
                {
                    playerOne.setPlayerJumpState(playerJumpState::UP);
                }
                break;
            //skok drugog igraca
            case GLUT_KEY_UP:
                if(playerTwo.getPlayerJumpState() == playerJumpState::GROUND)
                {
                    playerTwo.setPlayerJumpState(playerJumpState::UP);
                }
                break;
            default:
                break;
        }
    }
}

static void on_released_keyboard(int key, int x, int y)
{
    switch(key)
    {
        //pomeranje prvog igraca
        case GLUT_KEY_F3:
            playerOneRight = 0;
            break;
        case GLUT_KEY_F1:
            playerOneLeft = 0;
            break;

        //pomeranje drugog igraca
        case GLUT_KEY_RIGHT:
            playerTwoRight = 0;
            break;
        case GLUT_KEY_LEFT:
            playerTwoLeft = 0;
            break;
    }
}

static void on_timer(int value)
{
    /* Proverava se da li callback dolazi od odgovarajuceg tajmera. */
    if (value != 0)
        return;
    
    //azuriranje pozicija objekata ako je igra u toku
    if(game.GetGameState() == gameState::GAME_PLAYING)
    {
        //pomeranje prvog igraca
        if(playerOne.getXPos()<=PlayerFieldBorder && playerOneRight)
            playerOne.setXPos(playerOne.getXPos() + PlayerOnKeyboardMovement);
        
        if(playerOne.getXPos()>=-PlayerFieldBorder && playerOneLeft)
            playerOne.setXPos(playerOne.getXPos() - PlayerOnKeyboardMovement);

        //pomeranje drugog igraca
        if (playerTwo.getXPos() <= PlayerFieldBorder && playerTwoRight)
            playerTwo.setXPos(playerTwo.getXPos() + PlayerOnKeyboardMovement);
        
        if (playerTwo.getXPos() >= -PlayerFieldBorder && playerTwoLeft)
            playerTwo.setXPos(playerTwo.getXPos() - PlayerOnKeyboardMovement);
        
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
        else
        {
            /* Ako je u toku igra azuriramo tajmer. */
            msecs -= 20;
            if(msecs % 1000 == 0)
            {
                secs--;
            }
        }
        ball.Update();
        //skok igraca
        playerOne.PlayerJumpUpdate();
        playerTwo.PlayerJumpUpdate();
    };
    
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
    
    //igrac A (1) je pobedio
    if((game.GetPlayerAScore() == 3  && goal_timer == 0) 
        || (secs <= 0 && game.GetPlayerAScore() > game.GetPlayerBScore() && (goal_timer == 0 || goal_timer == 101)))
    {
        game.SetGameState(gameState::GAME_END);
        game.SetPlayerAScore(0);
        game.SetPlayerBScore(0);
        timer_active = 0;
        msecs = MsecsDefault;
        secs = SecsDefault;
        winnerText = (char *)"PLAYER 1 WINS";
    };
    
    //igrac B (2) je pobedio
    if((game.GetPlayerBScore() == 3  && goal_timer == 0) 
        || (secs <= 0 && game.GetPlayerAScore() < game.GetPlayerBScore()  && (goal_timer == 0 || goal_timer == 101)))
    {
        game.SetGameState(gameState::GAME_END);
        game.SetPlayerAScore(0);
        game.SetPlayerBScore(0);
        goal_timer = 101;
        ball.Reset();
        playerOne.Reset();
        playerTwo.Reset();
        timer_active = 0;
        msecs = MsecsDefault;
        secs = SecsDefault;
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

static void initialize(void)
{
    //KOD PREUZET SA CASOVA VEZBI
    
    /* Objekat koji predstavlja teskturu ucitanu iz fajla. */
    Image * image;

    /* Postavlja se boja pozadine. */
    glClearColor(0, 0, 0, 0);

    /* Ukljucuje se testiranje z-koordinate piksela. */
    glEnable(GL_DEPTH_TEST);

    /* Ukljucuju se teksture. */
    glEnable(GL_TEXTURE_2D);

    glTexEnvf(GL_TEXTURE_ENV,
              GL_TEXTURE_ENV_MODE,
              GL_ADD);

    /*
     * Inicijalizuje se objekat koji ce sadrzati teksture ucitane iz
     * fajla.
     */
    image = image_init(0, 0);

    /* Kreira se prva tekstura. */
    image_read(image, FILENAME0);

    /* Generisu se identifikatori tekstura. */
    glGenTextures(2, names);

    glBindTexture(GL_TEXTURE_2D, names[0]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    /* Kreira se druga tekstura. */
    image_read(image, FILENAME1);

    glBindTexture(GL_TEXTURE_2D, names[1]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    /* Iskljucujemo aktivnu teksturu */
    glBindTexture(GL_TEXTURE_2D, 0);

    /* Unistava se objekat za citanje tekstura iz fajla. */
    image_done(image);
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
    
    //Iscrtavanje teksture pozadine
    glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, names[0]);
    glPushMatrix();
        glColor3f(0.3, 0.8, 1.0);
        glBegin(GL_QUADS);
            //Brojke su u brzini rucno prilagodjene
            glTexCoord2f(0, 0);
            glVertex3f(-1050, -600, 0);
            glTexCoord2f(1, 0);
            glVertex3f(1050, -600, 0);
            glTexCoord2f(1, 1);
            glVertex3f(1050, 600, 0);
            glTexCoord2f(0, 1);
            glVertex3f(-1050, 600, 0);
        glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnable(GL_DEPTH_TEST);
    
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
        playground.drawField(names);
        playerOne.drawPlayer();
        playerTwo.drawPlayer();
        ball.drawBall();
        WritePoints();
        WriteInstructions();
        if(secs > 0)
        {    
            WriteTimer();
        }
        else
        {
            WriteGoldenGoal();
        }
        
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

static void WriteTimer()
{
    glDisable(GL_LIGHTING);
    glColor3f(1, 0, 0);    
    int i;
    
    glRasterPos3f(TimerX, TimerY, TimerZ);
    char timer[5];
    ConvertIntToChar(secs, timer);
    for(i = 0; timer[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, timer[i]);
    
	glEnable(GL_LIGHTING);
}

static void WriteGoldenGoal()
{
    glDisable(GL_LIGHTING);
	glColor3f(255, 223, 0);    
    int i;
    
    glRasterPos3f(GoldenGoalX, GoldenGoalY, GoldenGoalZ);
    char s[] = "GOLDEN GOAL";
    for(i = 0; s[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
    
	glEnable(GL_LIGHTING);
}

static void WriteInstructions()
{
    glDisable(GL_LIGHTING);
	glColor3f(0, 0, 0);    
    int i;
    
    glRasterPos3f(-600, PlayerAPointsY, PlayerAPointsZ);
    char s[] = "F1-Left | F3-Right | F2-Jump ";
    //char s[] = "A-Left D-Right W-Jump ";
    for(i = 0; s[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
    
    glRasterPos3f(200, PlayerAPointsY, PlayerAPointsZ);
    char p[] = "LEFT-Left | RIGHT-Right | UP-Jump ";
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
    if(x < 10)
    {
        s[0] = '0' + x; 
        s[1] = '\0';
        return;
    }
    else
    {
        s[0] = '0' + x/10;
        s[1] = '0' + x%10;
        s[2] = '\0';
        return;
    }
}
