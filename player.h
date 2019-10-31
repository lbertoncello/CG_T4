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

    Bomb *dropBomb(GLfloat deltaIdleTime);
};

#endif