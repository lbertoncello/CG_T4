#include "player.h"

Bomb* Player::dropBomb(GLfloat deltaIdleTime)
{
    GLfloat resultingAngle = calc.degreesToRadians(inclinationAngle);
    GLfloat bombSpeed = speedNorm;
    Point bombCoordinates = Point(dX, dY);
    Point bombBodyCoordinates = getCurrentPositionAdjusted();
    GLfloat bombRadius = this->body.getRadius() / 4.0;

    return new Bomb(bombBodyCoordinates, bombRadius, bombCoordinates, bombSpeed, resultingAngle);
}
