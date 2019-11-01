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
};

#endif