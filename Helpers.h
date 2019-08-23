#ifndef HELPERS_H
#define HELPERS_H

static int dvapet = 255;
static float pi = 3.1415926f;

//game
enum gameState
{
    GAME_START = 0,
    GAME_PLAYING = 1,
    GAME_END = 2
};

//writing 
static float StartScreenXPosition = -250.0;
static float StartScreenYPositionLine_1 = 200.0;
static float StartScreenYPositionLine_2 = 50.0;
static float StartScreenYPositionLine_3 = -50.0;
static float StartScreenZPosition = 0.0;

static float PlayerAPointsX = -30.0;
static float PlayerAPointsY = 400.0;
static float PlayerAPointsZ = 0.0;

static float PlayerBPointsX = 30.0;
static float PlayerBPointsY = 400.0;
static float PlayerBPointsZ = 0.0;

//ball
static float BallSize = 50.0;

//Player
static float PlayerBodySize = 90.0;

enum playerJumpState
{
    UP = 0,
    DOWN = 1,
    GROUND = 2
};

#endif

