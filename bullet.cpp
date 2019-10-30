#include "bullet.h"

void Bullet::move(GLfloat deltaIdleTime)
{
    dX += calcMovement_x(deltaIdleTime);
    dY += calcMovement_y(deltaIdleTime);
}

GLfloat Bullet::calcMovement_x(GLfloat deltaIdleTime)
{
    return speedNorm * deltaIdleTime * cos(moveAngle);
}

GLfloat Bullet::calcMovement_y(GLfloat deltaIdleTime)
{
    return speedNorm * deltaIdleTime * sin(moveAngle);
}

Point Bullet::getCurrentPositionAdjusted()
{
    Point currentPositionAdjusted;
    currentPositionAdjusted.setX(this->body.getCenter_x() - startPosition.getX() + dX);
    currentPositionAdjusted.setY(this->body.getCenter_y() - startPosition.getY() + dY);

    return currentPositionAdjusted;
}

void Bullet::draw()
{
    glPushMatrix();

    glTranslatef(dX, dY, 0.0);
    drawer.drawFilledCircle(this->body);

    glPopMatrix();
}