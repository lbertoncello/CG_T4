#ifndef BULLET_H
#define BULLET_H

#include "circle.h"
#include "draw.h"

class Bullet
{
    Circle body;
    GLfloat dX;
    GLfloat dY;
    GLfloat speedNorm;
    GLfloat moveAngle;
    Point startPosition;
    Draw drawer;

    GLfloat calcMovement_x(GLfloat deltaIdleTime);
    GLfloat calcMovement_y(GLfloat deltaIdleTime);

public:
    Bullet() {}

    Bullet(Circle body, Point moveCoordinates, GLfloat speedNorm, GLfloat moveAngle)
    {
        this->body = body;
        this->speedNorm = speedNorm;
        this->moveAngle = moveAngle;
        this->dX = moveCoordinates.getX();
        this->dY = moveCoordinates.getY();
    }

    Bullet(Point bodyCoordinates, GLfloat radius, Point moveCoordinates, GLfloat speedNorm, GLfloat moveAngle, Color color)
    {
        this->body = Circle(bodyCoordinates, radius, color);
        this->speedNorm = speedNorm;
        this->moveAngle = moveAngle;
        this->dX = moveCoordinates.getX();
        this->dY = moveCoordinates.getY();
    }

    Bullet(Point bodyCoordinates, GLfloat radius, Point moveCoordinates, GLfloat speedNorm, GLfloat moveAngle)
    {
        this->body = Circle(bodyCoordinates, radius, Color(1, 0, 1));
        this->speedNorm = speedNorm;
        this->moveAngle = moveAngle;
        this->dX = moveCoordinates.getX();
        this->dY = moveCoordinates.getY();
        this->startPosition.setX(dX);
        this->startPosition.setY(dY);
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

    void draw();
    void move(GLfloat deltaIdleTime);
    Point getCurrentPositionAdjusted();
};

#endif