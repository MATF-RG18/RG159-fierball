#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

class Ball
{
public:
    Ball()
    {
        _xPos = 0.0;
        _yPos = 300.0;
        _zPos = 0.0;
        _xSpeed = 0;
        _ySpeed = 12.1;
        _xDirection = 1;
        _PlayerAGoal = false;
        _PlayerBGoal = false;
    };
    
    ~Ball() {};
    
    void drawBall();
    void Update();
    
    void CheckHeadCollision(float x, float y);
    void CheckBodyCollision(float x, float y);
    
    //getters and setters
    float getXPos() { return _xPos; } 
    void setXPos(float x) { _xPos = x; }
    float getYPos() { return _yPos; }
    void setYPos(float y) { _yPos = y; }
    float getZPos() { return _zPos; }
    void setZPos(float z) { _zPos = z; }
    
    void setXSpeed(float speed) { _xSpeed = speed; }
    void setYSpeed(float speed) { _ySpeed = speed; }
    
    bool getPlayerAGoal() { return _PlayerAGoal; }
    void setPlayerAGoal(bool goal) { _PlayerAGoal = goal; }
    bool getPlayerBGoal() { return _PlayerBGoal; }
    void setPlayerBGoal(bool goal) { _PlayerBGoal = goal; }
    
    void Reset()
    {
        _xPos = 0.0;
        _yPos = 300.0;
        _zPos = 0.0;
        _xSpeed = 0;
        _ySpeed = 12.1;
        _xDirection = 1;
        _PlayerAGoal = false;
        _PlayerBGoal = false;
    }
    
private:
    float _xPos;
    float _yPos;
    float _zPos;
    
    float _xSpeed;
    float _ySpeed;
    int _xDirection;
    
    bool _PlayerAGoal;
    bool _PlayerBGoal;
};

