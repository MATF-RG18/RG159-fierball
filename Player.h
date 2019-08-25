#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "Helpers.h"

class Player
{
public:
    Player(int number) :
        _playerNumber(number)
        {
            switch (_playerNumber)
            {
                case 1:
                    _xPos = -PlayerInitialXPosition;
                    break;
                case 2:
                    _xPos = +PlayerInitialXPosition;
                    break;
            }
            _yPos = PlayerInitialYPosition;
            _zPos = 0;
            _playerJumpState = playerJumpState::GROUND;
        }
        
    void Reset();

    void drawPlayer();

    void drawHead();
    void drawBody();
    
    //azuriranje koordinata prilikom skoka igraca
    void PlayerJumpUpdate();

    //getters and setters
    float getXPos() { return _xPos; }
    void setXPos(float x) { _xPos = x; }
    float getYPos() { return _yPos; }
    void setYPos(float y) { _yPos = y; }
    float getZPos() { return _zPos; }
    void setZPos(float z) { _zPos = z; }
    
    void setPlayerJumpState(playerJumpState value) { _playerJumpState = value; }
    playerJumpState getPlayerJumpState() { return _playerJumpState; }
    
private:
    float _xPos;
    float _yPos;
    float _zPos;
    int _playerNumber;
    playerJumpState _playerJumpState;
};
