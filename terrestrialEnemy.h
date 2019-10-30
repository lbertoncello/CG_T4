#ifndef TERRESTRIAL_ENEMY_H
#define TERRESTRIAL_ENEMY_H

#include "enemy.h"
#include "draw.h"

class TerrestrialEnemy : public Enemy
{
private:
    Draw drawer;

public:
    TerrestrialEnemy() {}

    TerrestrialEnemy(Circle body) : Enemy(body) {}

    void draw();
};

#endif