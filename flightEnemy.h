#ifndef FLIGHT_ENEMY_H
#define FLIGHT_ENEMY_H

#include <random>
#include <functional>

#include "airplane.h"
#include "draw.h"

#define TURN_LEFT 0
#define TURN_RIGHT 1

class FlightEnemy : public Airplane
{
    Draw drawer;

public:
    FlightEnemy() {}

    FlightEnemy(Circle body) : Airplane(body) {}

    void autoMove(GLfloat deltaIdleTime);

    void setSpeed(vector<GLfloat> speed)
    {
        speedNorm = calc.norm(speed) * this->airplaneSpeedMultiplier;
        moveAngle = 0;

        this->speed[0] = (speedNorm * cos(45.0 * 3.14159265 / 180));
        this->speed[1] = (speedNorm * sin(45.0 * 3.14159265 / 180));
    }
};

#endif