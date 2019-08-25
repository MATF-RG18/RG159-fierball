#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "Helpers.h"

class Fan
{
public:
    Fan(int number, int row) :
        _playerNumber(number), _fanRow(row) 
        {
            if(_playerNumber == 1)
            {
                switch (_fanRow)
                {
                    case 0:
                        _xPos = -750;
                        _yPos = 70;
                        _zPos = -520;
                        break;
                    case 1:
                        _xPos = -800;
                        _yPos = 180;
                        _zPos = -600;
                        break;
                    case 2:
                        _xPos = -750;
                        _yPos = 290;
                        _zPos = -680;
                        break;
                }
            }
            
            if(_playerNumber == 2)
            {
                switch (_fanRow)
                {
                    case 0:
                        _xPos = 50;
                        _yPos = 70;
                        _zPos = -520;
                        break;
                    case 1:
                        _xPos = 0;
                        _yPos = 180;
                        _zPos = -600;
                        break;
                    case 2:
                        _xPos = 50;
                        _yPos = 290;
                        _zPos = -680;
                        break;
                }
            }
            _fanJumpState = playerJumpState::GROUND;
        }
        
    void Reset();

    void drawFan();

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
    int _fanRow;
};
