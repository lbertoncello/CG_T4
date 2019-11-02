#ifndef PLAYER_H
#define PLAYER_H

#include "airplane.h"
#include "bomb.h"

class Player : public Airplane
{
    GLfloat cannonAngle = 0.0;
    GLfloat propellerAngle = 0.0;

public:
    Player() {}

    Player(Circle body) : Airplane(body) {}

    void setSpeed(vector<GLfloat> speed)
    {
        speedNorm = calc.norm(speed) * this->airplaneSpeedMultiplier;
        moveAngle = -atan2f(speed[1], speed[0]);

        this->speed[0] = (speedNorm * cos(45.0 * 3.14159265 / 180.0));
        this->speed[1] = (speedNorm * sin(45.0 * 3.14159265 / 180.0));
    }

    Bomb *dropBomb(GLfloat deltaIdleTime);
};

#endif