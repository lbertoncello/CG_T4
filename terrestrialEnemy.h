#ifndef TERRESTRIAL_ENEMY_H
#define TERRESTRIAL_ENEMY_H

#include "enemy.h"
#include "draw.h"

class TerrestrialEnemy
{
private:
    Draw drawer;
    Circle body;
    Point currentPosition;
    Point startPosition;
    GLfloat dX;
    GLfloat dY;
    bool startPositionInitialized = false;

    bool destroyed = false;

public:
    TerrestrialEnemy() {}

    TerrestrialEnemy(Circle body)
    {
        this->body = body;
    }

    Circle &getBody()
    {
        return body;
    }

    Point getCurrentPosition()
    {
        return currentPosition;
    }

    bool isDestroyed()
    {
        return destroyed;
    }

    void setCurrentPosition(Point currentPosition)
    {
        if (startPositionInitialized == false)
        {
            startPosition.setX(currentPosition.getX());
            startPosition.setY(currentPosition.getY());
            startPositionInitialized = true;
        }

        dX = currentPosition.getX();
        dY = currentPosition.getY();

        this->currentPosition = currentPosition;
    }

    void setBody(Circle body)
    {
        this->body = body;
    }

    void setDestroyed(bool destroyed)
    {
        this->destroyed = destroyed;
    }

    Point getCurrentPositionAdjusted();
    Circle getAdjustedBody();
    void draw();
    void reset();
};

#endif