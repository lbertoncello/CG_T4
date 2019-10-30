#include "bomb.h"

void Bomb::calcSizeDecreaseAcceleration()
{
    GLfloat initialSize = this->body.getRadius();
    GLfloat finalSize = this->body.getRadius() / 2;

    sizeDecreaseAcceleration = calc.calcAccelerationRequired(initialSize, finalSize, 0, BOMB_LIFETIME);
}

GLfloat Bomb::calcCurrentRadiusVariation()
{
    GLfloat initialPosition = initialRadius;
    GLfloat acceleration = sizeDecreaseAcceleration;
    GLfloat initialSpeed = 0;

    currentTime = std::chrono::high_resolution_clock::now();
    duration<GLfloat> timeSpan = duration_cast<duration<GLfloat>>(currentTime - dropStartTime);
    GLfloat sizeDecreaseTimeElapsed = timeSpan.count();

    if (sizeDecreaseTimeElapsed >= BOMB_LIFETIME)
    {
        onTheGround = true;
    }

    return calc.calcCurrentPositionVariation(initialPosition, acceleration, initialSpeed, sizeDecreaseTimeElapsed);
}

void Bomb::updateSize()
{
    GLfloat newRadius = initialRadius + calcCurrentRadiusVariation();
    this->body.setRadius(newRadius);
}

void Bomb::move(GLfloat deltaIdleTime)
{
    dX += calcMovement_x(deltaIdleTime);
    dY += calcMovement_y(deltaIdleTime);
}

GLfloat Bomb::calcMovement_x(GLfloat deltaIdleTime)
{
    return speedNorm * deltaIdleTime * cos(moveAngle);
}

GLfloat Bomb::calcMovement_y(GLfloat deltaIdleTime)
{
    return speedNorm * deltaIdleTime * sin(moveAngle);
}

Point Bomb::getCurrentPositionAdjusted()
{
    Point currentPositionAdjusted;
    currentPositionAdjusted.setX(this->body.getCenter_x() - startPosition.getX() + dX);
    currentPositionAdjusted.setY(this->body.getCenter_y() - startPosition.getY() + dY);

    return currentPositionAdjusted;
}

void Bomb::draw()
{
    glPushMatrix();

    glTranslatef(dX, dY, 0.0);
    drawer.drawFilledCircle(this->body);

    glPopMatrix();
}