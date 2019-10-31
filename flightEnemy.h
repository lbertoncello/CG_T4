#ifndef FLIGHT_ENEMY_H
#define FLIGHT_ENEMY_H

#include "airplane.h"
#include "draw.h"

class FlightEnemy : public Airplane
{
    Draw drawer;

public:
    FlightEnemy() {}

    FlightEnemy(Circle body) : Airplane(body) {}

    // void draw();
};

#endif