#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "Helpers.h"

class Game
{
public:
    Game()
    {
        _gameState = gameState::GAME_START;
        _playerAScore = 0;
        _playerBScore = 0;
    };
    
    void SetGameState(gameState value) {_gameState = value; };
    gameState GetGameState() { return _gameState; };
    
    int GetPlayerAScore () { return _playerAScore; };
    int GetPlayerBScore () { return _playerBScore; };
    
    void SetPlayerAScore(int value) {_playerAScore = value; };
    void SetPlayerBScore(int value) {_playerBScore = value; };
    
    void IncreasePlayerAScore() { _playerAScore++; };
    void IncreasePlayerBScore() { _playerBScore++; };
    
private:    
    gameState _gameState;
    int _playerAScore;
    int _playerBScore;
};
