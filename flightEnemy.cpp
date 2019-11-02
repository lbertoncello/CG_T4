#include "flightEnemy.h"

void FlightEnemy::autoMove(GLfloat deltaIdleTime)
{
    std::random_device r;
    auto randomGenerator = std::bind(std::uniform_int_distribution<>(0, 1), std::default_random_engine(r()));

    if (randomGenerator() == TURN_LEFT)
    {
        this->setTurningLeft(true);
        this->setTurningRight(false);
    }
    else
    {
        this->setTurningLeft(false);
        this->setTurningRight(true);
    }

    this->move(deltaIdleTime);
}