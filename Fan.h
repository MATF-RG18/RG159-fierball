#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "Helpers.h"

class Fan
{
public:
    Fan(int number) :
        _playerNumber(number)
        {
        switch (_playerNumber)
        {
            case 1:
                _xPos = -750.0;
                break;
            case 2:
                _xPos = 50.0;
                break;
        }
            _yPos = 70;//100.0;
            _zPos = -520;//-500.0;
            _fanJumpState = playerJumpState::GROUND;
        }
        
    void Reset()
    {
        _yPos = 70;//100.0;
        _fanJumpState = playerJumpState::GROUND;
    }

    void drawFan();

    //head
    void drawHead();

    void drawBody();
    
    void FanJumpUpdate();

    //getters and setters
    float getXPos() { return _xPos; }
    void setXPos(float x) { _xPos = x; }
    float getYPos() { return _yPos; }
    void setYPos(float y) { _yPos = y; }
    float getZPos() { return _zPos; }
    void setZPos(float z) { _zPos = z; }
    
    void setFanJumpState(playerJumpState value) { _fanJumpState = value; }
    playerJumpState getFanJumpState() { return _fanJumpState; }
    
private:
    float _xPos;
    float _yPos;
    float _zPos;
    int _playerNumber;
    playerJumpState _fanJumpState;
};
