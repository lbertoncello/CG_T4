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
    GLint autoMoveDirection;

public:
    FlightEnemy() {}

    FlightEnemy(Circle body) : Airplane(body)
    {
        std::random_device r;
        auto randomGenerator = std::bind(std::uniform_int_distribution<>(0, 1), std::default_random_engine(r()));

        autoMoveDirection = randomGenerator();
    }

    void autoMove(GLfloat deltaIdleTime);
};

#endif