#include "flightEnemy.h"

void FlightEnemy::autoMove(GLfloat deltaIdleTime) {
    if(autoMoveDirection == TURN_LEFT) {
        this->setTurningLeft(true);
    } else {
        this->setTurningRight(true);
    }

    this->move(deltaIdleTime);
}