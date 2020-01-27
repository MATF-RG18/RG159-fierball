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

//fanovi
const static float X_DistanceBeetwenFans = 110.0;

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

const static float TimerX = -15.0;
const static float TimerY = 470.0;
const static float TimerZ = 0.0;

const static float GoldenGoalX = -120.0;
const static float GoldenGoalY = 470.0;
const static float GoldenGoalZ = 0.0;

const static int SecsDefault = 60;
const static int MsecsDefault = 60000;

//lopta
const static float BallSize = 50.0;

//igrac
const static float PlayerBodySize = 90.0;
const static float PlayerInitialXPosition = 500.0;
const static float PlayerInitialYPosition = -60.0;
const static float PlayerHeadSize = 50.0;
const static float PlayerMaxJumpYHeight = 100.0;
const static float PlayerOnKeyboardMovement = 15.0;
const static float PlayerFieldBorder = 595.0;
enum playerJumpState
{
    UP = 0,
    DOWN = 1,
    GROUND = 2
};

#endif

