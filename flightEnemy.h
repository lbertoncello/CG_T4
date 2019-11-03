#ifndef FLIGHT_ENEMY_H
#define FLIGHT_ENEMY_H

#include <random>
#include <functional>
#include <ctime>
#include <ratio>
#include <chrono>

#include "airplane.h"
#include "draw.h"

#define TURN_LEFT 0
#define TURN_RIGHT 1

using namespace std::chrono;

class FlightEnemy : public Airplane
{
    Draw drawer;
    GLfloat shotsFrequency;
    high_resolution_clock::time_point lastShotStartTime;
    high_resolution_clock::time_point currentTime;
    GLfloat timeToShot = 0;

public:
    FlightEnemy() {}

    FlightEnemy(Circle body, GLfloat airplaneSpeedMultiplier, GLfloat bulletSpeedMultiplier, GLfloat shotsFrequency) : Airplane(body, airplaneSpeedMultiplier, bulletSpeedMultiplier)
    {
        this->shotsFrequency = shotsFrequency;
        this->timeToShot = 1.0 / shotsFrequency;
    }

    void autoMove(GLfloat deltaIdleTime);
    bool checkAutoShot();
    Bullet* autoShoot(GLfloat deltaIdleTime);
};

#endif