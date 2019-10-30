#ifndef PLAYER_AIRPLANE_H
#define PLAYER_AIRPLANE_H

#include "circle.h"
#include "bullet.h"
#include "bomb.h"
#include "draw.h"
#include "calc.h"

#define MOVE_UP 1
#define MOVE_DOWN 2
#define MOVE_LEFT 3
#define MOVE_RIGHT 4

#define PI 3.14159265
class PlayerAirplane
{
    Circle body;
    Point currentPosition;
    Point startPosition;
    GLfloat initialRadius;
    GLfloat dX = 0; //variação em X
    GLfloat dY = 0; //variação em Y
    GLfloat inclinationAngle = 0;
    GLfloat speedNorm = 0;
    GLfloat speedIncrement = 5;
    bool turningLeft = false;
    bool turningRight = false;
    bool flying = false;
    bool takingOff = false;
    bool startPositionInitialized = false;
    bool initialRadiusInitialized = false;
    Draw drawer;
    vector<GLfloat> speed;
    GLfloat moveAngle;
    GLfloat airplaneSpeedMultiplier = 1.0;
    GLfloat bulletSpeedMultiplier = 1.0;
    Calc calc;
    GLfloat cannonAngle = 0.0;
    GLfloat propellerAngle = 0.0;

    void speedInit()
    {
        speed.push_back(0);
        speed.push_back(0);
    }

    void drawMainBody();
    void drawTail();
    void drawCockpit();
    void drawWings();
    void drawPropeller();
    void drawCannon();
    void updateTurnRightAngle(GLfloat deltaIdleTime);
    void updateTurnLeftAngle(GLfloat deltaIdleTime);
    GLfloat getNextMoveAngle(GLfloat deltaIdleTime);
    GLfloat calcNextMovement_x(GLfloat deltaIdleTime, GLfloat nextMoveAngle);
    GLfloat calcNextMovement_y(GLfloat deltaIdleTime, GLfloat nextMoveAngle);
    void updateInclinationAngle(GLfloat deltaIdleTime);
    Point getPositionAdjusted(Point position);

public:
    PlayerAirplane()
    {
        speedInit();
    }

    PlayerAirplane(Circle body)
    {
        this->body = body;
        initialRadius = body.getRadius();
        initialRadiusInitialized = true;
        speedInit();
    }

    Circle &getBody()
    {
        return body;
    }

    Point getCurrentPosition()
    {
        return currentPosition;
    }

    Point getStartPosition()
    {
        return startPosition;
    }

    GLfloat getInitialRadius()
    {
        return initialRadius;
    }

    bool isFlying()
    {
        return flying;
    }

    bool isTakingOff()
    {
        return takingOff;
    }

    bool isTurningLeft()
    {
        return turningLeft;
    }

    bool isTurningRight()
    {
        return turningRight;
    }

    vector<GLfloat> &getSpeed()
    {
        return speed;
    }

    GLfloat getSpeedMultiplier()
    {
        return airplaneSpeedMultiplier;
    }

    GLfloat getSpeedNorm()
    {
        return speedNorm;
    }

    GLfloat getSpeedIncrement()
    {
        return speedIncrement;
    }

    void setBody(Circle body)
    {
        this->body = body;

        if (initialRadiusInitialized == false)
        {
            initialRadius = body.getRadius();
            initialRadiusInitialized = true;
        }
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

    void setFlying(bool flying)
    {
        this->flying = flying;
    }

    void setTakingOff(bool takingOff)
    {
        this->takingOff = takingOff;
    }

    void setSpeed(vector<GLfloat> speed)
    {
        speedNorm = calc.norm(speed) * this->airplaneSpeedMultiplier;
        moveAngle = -atan2f(speed[1], speed[0]);

        this->speed[0] = (speedNorm * cos(45.0 * 3.14159265 / 180));
        this->speed[1] = (speedNorm * sin(45.0 * 3.14159265 / 180));
    }

    void setSpeedNorm(GLfloat speedNorm)
    {
        this->speedNorm = speedNorm;
    }

    void setAirplaneSpeedMultiplier(GLfloat airplaneSpeedMultiplier)
    {
        this->airplaneSpeedMultiplier = airplaneSpeedMultiplier;
    }

    void setInclinationAngle(GLfloat inclinationAngle)
    {
        this->inclinationAngle = inclinationAngle;
    }

    GLfloat getInclinationAngle()
    {
        return this->inclinationAngle;
    }

    void setBulletSpeedMultiplier(GLfloat bulletSpeedMultiplier)
    {
        this->bulletSpeedMultiplier = bulletSpeedMultiplier;
    }

    void setTurningLeft(bool turningLeft)
    {
        this->turningLeft = turningLeft;
    }

    void setTurningRight(bool turningRight)
    {
        this->turningRight = turningRight;
    }

    void setSpeedIncrement(GLfloat speedIncrement)
    {
        this->speedIncrement = speedIncrement;
    }

    void incrementPropellerAngle()
    {
        this->propellerAngle += 0.10 * speedNorm;
    }

    void setPropellerAngle(GLfloat propellerAngle)
    {
        this->propellerAngle = propellerAngle;
    }

    void draw();
    void move(GLfloat deltaIdleTime);
    bool checkIntersection(Circle flightAreaBody, Circle enemyBody, GLfloat deltaIdleTime);
    GLfloat calcMovement_x(GLfloat deltaIdleTime);
    GLfloat calcMovement_y(GLfloat deltaIdleTime);
    Circle getAdjustedBody();
    bool isInside(Circle circle, GLint moveDirection, GLfloat deltaIdleTime);
    Point getNextPosition(GLfloat deltaIdleTime);
    void updateTurningAngles(GLfloat deltaIdleTime);
    void incrementSpeed();
    void incrementSpeed(GLfloat speedIncrement);
    void decrementSpeed();
    void decrementSpeed(GLfloat speedIncrement);
    void reset();
    void teleport();
    Point getCurrentPositionAdjusted();
    void rotateCannon(GLfloat moviment, GLfloat deltaIdleTime);
    Bullet *shoot(GLfloat deltaIdleTime);
    Bomb *dropBomb(GLfloat deltaIdleTime);
};

#endif