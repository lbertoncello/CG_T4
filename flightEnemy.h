#ifndef FLIGHT_ENEMY_H
#define FLIGHT_ENEMY_H

#include "enemy.h"
#include "draw.h"

class FlightEnemy : public Enemy
{
    Draw drawer;

public:
    FlightEnemy() {}

    FlightEnemy(Circle body) : Enemy(body) {}

    void draw();
};

#endif