#ifndef HELPERS_H
#define HELPERS_H

//konstante koje se cesto koriste
const static float PI = 3.1415926f;

//game
enum gameState
{
    GAME_START = 0,
    GAME_PLAYING = 1,
    GAME_END = 2
};

//ispis na ekranu
const static float StartScreenXPosition = -250.0;
const static float StartScreenYPositionLine_1 = 200.0;
const static float StartScreenYPositionLine_2 = 50.0;
const static float StartScreenYPositionLine_3 = -50.0;
const static float StartScreenZPosition = 0.0;

const static float PlayerAPointsX = -30.0;
const static float PlayerAPointsY = 400.0;
const static float PlayerAPointsZ = 0.0;

const static float PlayerBPointsX = 30.0;
const static float PlayerBPointsY = 400.0;
const static float PlayerBPointsZ = 0.0;

//lopta
const static float BallSize = 50.0;

//igrac
const static float PlayerBodySize = 90.0;
const static float PlayerInitialXPosition = 500.0;
const static float PlayerInitialYPosition = -60.0;
const static float PlayerHeadSize = 50.0;
const static float PlayerMaxJumpYHeight = 100.0;
enum playerJumpState
{
    UP = 0,
    DOWN = 1,
    GROUND = 2
};

#endif

