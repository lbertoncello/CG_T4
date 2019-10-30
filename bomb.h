#ifndef BOMB_H
#define BOMB_H

#include <ctime>
#include <ratio>
#include <chrono>

#include "circle.h"
#include "draw.h"
#include "calc.h"

using namespace std::chrono;
using namespace std;

#define BOMB_LIFETIME 4.0

class Bomb
{
    Circle body;
    GLfloat dX;
    GLfloat dY;
    GLfloat speedNorm;
    GLfloat moveAngle;
    Point startPosition;
    Draw drawer;
    Calc calc;
    GLfloat initialRadius;
    GLfloat sizeDecreaseAcceleration;
    high_resolution_clock::time_point dropStartTime;
    high_resolution_clock::time_point currentTime;
    bool onTheGround = false;

    void calcSizeDecreaseAcceleration();
    GLfloat calcCurrentRadiusVariation();
    GLfloat calcMovement_x(GLfloat deltaIdleTime);
    GLfloat calcMovement_y(GLfloat deltaIdleTime);

public:
    Bomb() {}

    Bomb(Circle body, Point moveCoordinates, GLfloat speedNorm, GLfloat moveAngle)
    {
        this->body = body;
        this->speedNorm = speedNorm;
        this->moveAngle = moveAngle;
        this->dX = moveCoordinates.getX();
        this->dY = moveCoordinates.getY();
        dropStartTime = std::chrono::high_resolution_clock::now();
        currentTime = std::chrono::high_resolution_clock::now();
        initialRadius = this->body.getRadius();
        calcSizeDecreaseAcceleration();
    }

    Bomb(Point bodyCoordinates, GLfloat radius, Point moveCoordinates, GLfloat speedNorm, GLfloat moveAngle, Color color)
    {
        this->body = Circle(bodyCoordinates, radius, color);
        this->speedNorm = speedNorm;
        this->moveAngle = moveAngle;
        this->dX = moveCoordinates.getX();
        this->dY = moveCoordinates.getY();
        dropStartTime = std::chrono::high_resolution_clock::now();
        currentTime = std::chrono::high_resolution_clock::now();
        initialRadius = this->body.getRadius();
        calcSizeDecreaseAcceleration();
    }

    Bomb(Point bodyCoordinates, GLfloat radius, Point moveCoordinates, GLfloat speedNorm, GLfloat moveAngle)
    {
        this->body = Circle(bodyCoordinates, radius, Color(0.65, 0.2, 0.45));
        this->speedNorm = speedNorm;
        this->moveAngle = moveAngle;
        this->dX = moveCoordinates.getX();
        this->dY = moveCoordinates.getY();
        this->startPosition.setX(dX);
        this->startPosition.setY(dY);
        dropStartTime = std::chrono::high_resolution_clock::now();
        currentTime = std::chrono::high_resolution_clock::now();
        initialRadius = this->body.getRadius();
        calcSizeDecreaseAcceleration();
    }

    Circle &getBody()
    {
        return body;
    }

    GLfloat getSpeed()
    {
        return speedNorm;
    }

    GLfloat getspeedAngle()
    {
        return moveAngle;
    }

    bool isOnTheGround()
    {
        return onTheGround;
    }

    void draw();
    void move(GLfloat deltaIdleTime);
    void updateSize();
    Point getCurrentPositionAdjusted();
};

#endif