#include "playerAirplane.h"

void PlayerAirplane::draw()
{
    glPushMatrix();
    glTranslatef(dX, dY, 0.0);
    glRotatef(inclinationAngle, 0.0, 0.0, 1.0);

    drawWings();
    drawCannon();
    drawMainBody();
    drawCockpit();
    drawTail();
    glPopMatrix();
}

void PlayerAirplane::drawMainBody()
{
    drawer.drawEllipse(this->body);
}

void PlayerAirplane::drawTail()
{
    glPushMatrix();

    Color color(0.0, 0.0, 0.0);

    glTranslatef(-this->body.getRadius() / 2, 0.0, 0.0);
    glRotatef(90, 0.0, 0.0, 1.0);
    drawer.drawRectangle(this->body.getRadius() / 5, this->body.getRadius() / 2, color);

    glPopMatrix();
}

void PlayerAirplane::drawCockpit()
{
    glPushMatrix();

    GLfloat cockpitRadius = this->body.getRadius() / 2;
    Color cockpitColor(0.0, 0.0, 0.0);

    glTranslatef(this->body.getRadius() / 3, 0.0, 0.0);
    drawer.drawEllipse(cockpitRadius, cockpitColor);

    glPopMatrix();
}

void PlayerAirplane::drawWings()
{
    Color wingsColor(0.0, 0.0, 0.0);

    glPushMatrix();
    Point p1(0, 0);
    Point p2(p1.getX() + this->body.getRadius() / 3, p1.getY());
    Point p3(p1.getX() - this->body.getRadius() / 6, this->body.getRadius());
    Point p4(p1.getX() + this->body.getRadius() / 3 - this->body.getRadius() / 6, this->body.getRadius());

    glPushMatrix();

    glTranslatef(0, this->body.getRadius() / 2, 0.0);
    drawPropeller();

    glPopMatrix();

    drawer.drawRectangle(p4, p2, p1, p3, wingsColor);

    glPopMatrix();

    glPushMatrix();
    Point p5(0, 0);
    Point p6(p1.getX() + this->body.getRadius() / 3, p1.getY());
    Point p7(p1.getX() - this->body.getRadius() / 6, -this->body.getRadius());
    Point p8(p1.getX() + this->body.getRadius() / 3 - this->body.getRadius() / 6, -this->body.getRadius());

    glPushMatrix();

    glTranslatef(0, -this->body.getRadius() / 2, 0.0);
    drawPropeller();

    glPopMatrix();

    drawer.drawRectangle(p6, p8, p7, p5, wingsColor);

    glPopMatrix();
}

void PlayerAirplane::drawPropeller()
{
    Color rodColor(0.0, 0.0, 0.0);

    glPushMatrix();

    glRotatef(-90, 0.0, 0.0, 1.0);
    drawer.drawRectangle(this->body.getRadius() / 5.0, this->body.getRadius() / 2.5, rodColor);

    glPopMatrix();

    glPushMatrix();

    Color propellerColor(1.0, 1.0, 0.0);

    Point p1(-this->body.getRadius() / 4, -this->body.getRadius() / 6);
    Point p2(this->body.getRadius() / 4, -this->body.getRadius() / 6);
    Point p3(0, 0);

    Point p4(-this->body.getRadius() / 4, this->body.getRadius() / 6);
    Point p5(this->body.getRadius() / 4, this->body.getRadius() / 6);
    Point p6(0, 0);

    incrementPropellerAngle();
    glTranslatef(this->body.getRadius() / 2.0, 0, 0.0);
    glRotatef(propellerAngle, 1.0, 0.0, 0.0);

    drawer.drawTriangle(p3, p2, p1, propellerColor);
    drawer.drawTriangle(p4, p5, p6, propellerColor);

    glPopMatrix();
}

void PlayerAirplane::drawCannon()
{
    glPushMatrix();

    Color color(0.0, 0.0, 0.0);

    glTranslatef(this->body.getRadius() * 0.9, 0.0, 0.0);
    glRotatef(-90 + calc.radiansToDegrees(cannonAngle), 0.0, 0.0, 1.0);
    drawer.drawRectangle(this->body.getRadius() / 5, this->body.getRadius() / 2, color);

    glPopMatrix();
}

GLfloat PlayerAirplane::calcMovement_x(GLfloat deltaIdleTime)
{
    return speedNorm * deltaIdleTime * cos(moveAngle);
}

GLfloat PlayerAirplane::calcMovement_y(GLfloat deltaIdleTime)
{
    return speedNorm * deltaIdleTime * sin(moveAngle);
}

void PlayerAirplane::move(GLfloat deltaIdleTime)
{
    updateTurnLeftAngle(deltaIdleTime);
    updateTurnRightAngle(deltaIdleTime);
    updateInclinationAngle(deltaIdleTime);

    dX += calcMovement_x(deltaIdleTime);
    dY -= calcMovement_y(deltaIdleTime);
}

void PlayerAirplane::updateTurningAngles(GLfloat deltaIdleTime)
{
    updateTurnLeftAngle(deltaIdleTime);
    updateTurnRightAngle(deltaIdleTime);
}

GLfloat PlayerAirplane::calcNextMovement_x(GLfloat deltaIdleTime, GLfloat nextMoveAngle)
{
    return speedNorm * deltaIdleTime * cos(nextMoveAngle);
}

GLfloat PlayerAirplane::calcNextMovement_y(GLfloat deltaIdleTime, GLfloat nextMoveAngle)
{
    return speedNorm * deltaIdleTime * sin(nextMoveAngle);
}

Point PlayerAirplane::getNextPosition(GLfloat deltaIdleTime)
{
    GLfloat nextMoveAngle = getNextMoveAngle(deltaIdleTime);
    Point nextPosition;

    nextPosition.setX(dX + calcNextMovement_x(deltaIdleTime, nextMoveAngle));
    nextPosition.setY(dY - calcNextMovement_y(deltaIdleTime, nextMoveAngle));

    return nextPosition;
}

bool PlayerAirplane::checkIntersection(Circle flightAreaBody, Circle enemyBody, GLfloat deltaIdleTime)
{
    Circle adjustedBody = Circle(this->getNextPosition(deltaIdleTime), this->body.getRadius());
    adjustedBody.setCenter_x(flightAreaBody.getCenter_x() + adjustedBody.getCenter_x());
    adjustedBody.setCenter_y(flightAreaBody.getCenter_y() + adjustedBody.getCenter_y());

    return adjustedBody.checkIntersection(enemyBody, this->drawer.getNumSegments());
}

bool PlayerAirplane::isInside(Circle circle, GLint moveDirection, GLfloat deltaIdleTime)
{
    Circle adjustedBody = this->body;
    adjustedBody.setCenter_x(circle.getCenter_x() + this->dX);
    adjustedBody.setCenter_y(circle.getCenter_y() + this->dY);

    switch (moveDirection)
    {
    case MOVE_UP:
        adjustedBody.setCenter_y(adjustedBody.getCenter_y() - calcMovement_y(deltaIdleTime));
        break;
    case MOVE_DOWN:
        adjustedBody.setCenter_y(adjustedBody.getCenter_y() + calcMovement_y(deltaIdleTime));
        break;
    case MOVE_LEFT:
        adjustedBody.setCenter_x(adjustedBody.getCenter_x() - calcMovement_x(deltaIdleTime));
        break;
    case MOVE_RIGHT:
        adjustedBody.setCenter_x(adjustedBody.getCenter_x() + calcMovement_x(deltaIdleTime));
        break;
    }

    return circle.isInside(adjustedBody, this->drawer.getNumSegments());
}

Circle PlayerAirplane::getAdjustedBody()
{
    Circle adjustedBody = this->body;
    adjustedBody.setCenter_x(adjustedBody.getCenter_x() + this->dX);
    adjustedBody.setCenter_y(adjustedBody.getCenter_y() + this->dY);

    return adjustedBody;
}

GLfloat PlayerAirplane::getNextMoveAngle(GLfloat deltaIdleTime)
{
    GLfloat nextAngle = moveAngle;

    if (isTurningLeft())
    {
        nextAngle += (PI / 2 * deltaIdleTime);
    }

    if (isTurningRight())
    {
        nextAngle -= (PI / 2 * deltaIdleTime);
    }

    return nextAngle;
}

void PlayerAirplane::updateTurnRightAngle(GLfloat deltaIdleTime)
{
    if (isTurningRight())
    {
        moveAngle -= PI / 2 * deltaIdleTime;
    }
}

void PlayerAirplane::updateTurnLeftAngle(GLfloat deltaIdleTime)
{
    if (isTurningLeft())
    {
        moveAngle += PI / 2 * deltaIdleTime;
    }
}

void PlayerAirplane::updateInclinationAngle(GLfloat deltaIdleTime)
{
    GLfloat nextAngle = inclinationAngle;

    if (isTurningLeft())
    {
        nextAngle -= (90 * deltaIdleTime);
    }

    if (isTurningRight())
    {
        nextAngle += (90 * deltaIdleTime);
    }

    inclinationAngle = nextAngle;
}

void PlayerAirplane::reset()
{
    body.setRadius(initialRadius);
    dX = 0; //variação em X
    dY = 0; //variação em Y
    inclinationAngle = 0;
    speedNorm = 0.0;
    turningLeft = false;
    turningRight = false;
    flying = false;
    takingOff = false;
    startPositionInitialized = false;
    initialRadiusInitialized = false;
    cannonAngle = 0.0;
    propellerAngle = 0.0;
}

void PlayerAirplane::incrementSpeed()
{
    speedNorm += speedIncrement;
}

void PlayerAirplane::incrementSpeed(GLfloat speedIncrement)
{
    speedNorm += speedIncrement;
}

void PlayerAirplane::decrementSpeed()
{
    speedNorm -= speedIncrement;

    if (speedNorm < 0)
    {
        speedNorm = 0;
    }
}

void PlayerAirplane::decrementSpeed(GLfloat speedIncrement)
{
    speedNorm -= speedIncrement;

    if (speedNorm < 0)
    {
        speedNorm = 0;
    }
}

void PlayerAirplane::teleport()
{
    GLfloat x = dX;
    GLfloat y = dY;

    GLfloat alpha = atan2(y, x) * 180 / M_PI;
    GLfloat beta = (calc.degreesToRadians(this->inclinationAngle) - M_PI / 2) * 180 / M_PI;
    GLfloat theta = (-2 * (alpha - beta)) * M_PI / 180;

    this->dX = (x * cos(theta)) - (y * sin(theta));
    this->dY = (x * sin(theta)) + (y * cos(theta));
}

Point PlayerAirplane::getCurrentPositionAdjusted()
{
    Point currentPositionAdjusted;
    currentPositionAdjusted.setX(this->body.getCenter_x() + dX - this->startPosition.getX());
    currentPositionAdjusted.setY(this->body.getCenter_y() + dY - this->startPosition.getY());

    return currentPositionAdjusted;
}

Point PlayerAirplane::getPositionAdjusted(Point position)
{
    Point currentPositionAdjusted;
    currentPositionAdjusted.setX(this->body.getCenter_x() + position.getX() - this->startPosition.getX());
    currentPositionAdjusted.setY(this->body.getCenter_y() + position.getY() - this->startPosition.getY());

    return currentPositionAdjusted;
}

void PlayerAirplane::rotateCannon(GLfloat moviment, GLfloat deltaIdleTime)
{
    GLfloat nextCannonAngle = this->cannonAngle + moviment * 0.1 * deltaIdleTime;

    if (nextCannonAngle > PI / 4.0)
    {
        cannonAngle = PI / 4.0;
    }
    else if (nextCannonAngle < -PI / 4.0)
    {
        cannonAngle = -PI / 4.0;
    } else {
        cannonAngle = nextCannonAngle;
    }
}

Bullet* PlayerAirplane::shoot(GLfloat deltaIdleTime)
{
    GLfloat resultingAngle = calc.degreesToRadians(inclinationAngle) + cannonAngle;
    GLfloat bulletSpeed = speedNorm * bulletSpeedMultiplier;
    GLfloat bulletRadius = this->body.getRadius() / 8.0;
    Point bulletCoordinates;

    bulletCoordinates.setX(
        dX + body.getRadius() * cos(calc.degreesToRadians(inclinationAngle)) + this->body.getRadius() / 2 * cos(resultingAngle));
    bulletCoordinates.setY(
        dY + body.getRadius() * sin(calc.degreesToRadians(inclinationAngle)) + this->body.getRadius() / 2 * sin(resultingAngle));

    Point bulletBodyCoordinates = getPositionAdjusted(bulletCoordinates);

    return new Bullet(bulletBodyCoordinates, bulletRadius, bulletCoordinates, bulletSpeed, resultingAngle);
}

Bomb* PlayerAirplane::dropBomb(GLfloat deltaIdleTime)
{
    GLfloat resultingAngle = calc.degreesToRadians(inclinationAngle);
    GLfloat bombSpeed = speedNorm;
    Point bombCoordinates = Point(dX, dY);
    Point bombBodyCoordinates = getCurrentPositionAdjusted();
    GLfloat bombRadius = this->body.getRadius() / 4.0;

    return new Bomb(bombBodyCoordinates, bombRadius, bombCoordinates, bombSpeed, resultingAngle);
}
