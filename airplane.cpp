#include "airplane.h"

// void Airplane::draw()
// {
//     glPushMatrix();
//     glTranslatef(dX, dY, 0.0);
//     glRotatef(inclinationAngle, 0.0, 0.0, 1.0);

//     drawWings();
//     drawCannon();
//     drawMainBody();
//     drawCockpit();
//     drawTail();
//     glPopMatrix();
// }

void Airplane::draw()
{
    if (!isDestroyed())
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
}

void Airplane::drawMainBody()
{
    drawer.drawEllipse(this->body);
}

void Airplane::drawTail()
{
    glPushMatrix();

    Color color(0.0, 0.0, 0.0);

    glTranslatef(-this->body.getRadius() / 2, 0.0, 0.0);
    glRotatef(90, 0.0, 0.0, 1.0);
    drawer.drawRectangle(this->body.getRadius() / 5.0, this->body.getRadius() / 2.0, color);

    glPopMatrix();
}

void Airplane::drawCockpit()
{
    glPushMatrix();

    GLfloat cockpitRadius = this->body.getRadius() / 2.0;
    Color cockpitColor(0.0, 0.0, 0.0);

    glTranslatef(this->body.getRadius() / 3.0, 0.0, 0.0);
    drawer.drawEllipse(cockpitRadius, cockpitColor);

    glPopMatrix();
}

void Airplane::drawWings()
{
    Color wingsColor(0.0, 0.0, 0.0);

    glPushMatrix();
    Point p1(0.0, 0.0);
    Point p2(p1.getX() + this->body.getRadius() / 3.0, p1.getY());
    Point p3(p1.getX() - this->body.getRadius() / 6.0, this->body.getRadius());
    Point p4(p1.getX() + this->body.getRadius() / 3.0 - this->body.getRadius() / 6.0, this->body.getRadius());

    glPushMatrix();

    glTranslatef(0, this->body.getRadius() / 2.0, 0.0);
    drawPropeller();

    glPopMatrix();

    drawer.drawRectangle(p4, p2, p1, p3, wingsColor);

    glPopMatrix();

    glPushMatrix();
    Point p5(0.0, 0.0);
    Point p6(p1.getX() + this->body.getRadius() / 3.0, p1.getY());
    Point p7(p1.getX() - this->body.getRadius() / 6.0, -this->body.getRadius());
    Point p8(p1.getX() + this->body.getRadius() / 3.0 - this->body.getRadius() / 6.0, -this->body.getRadius());

    glPushMatrix();

    glTranslatef(0, -this->body.getRadius() / 2.0, 0.0);
    drawPropeller();

    glPopMatrix();

    drawer.drawRectangle(p6, p8, p7, p5, wingsColor);

    glPopMatrix();
}

void Airplane::drawPropeller()
{
    Color rodColor(0.0, 0.0, 0.0);

    glPushMatrix();

    glRotatef(-90, 0.0, 0.0, 1.0);
    drawer.drawRectangle(this->body.getRadius() / 5.0, this->body.getRadius() / 2.5, rodColor);

    glPopMatrix();

    glPushMatrix();

    Color propellerColor(1.0, 1.0, 0.0);

    Point p1(-this->body.getRadius() / 4.0, -this->body.getRadius() / 6.0);
    Point p2(this->body.getRadius() / 4.0, -this->body.getRadius() / 6.0);
    Point p3(0.0, 0.0);

    Point p4(-this->body.getRadius() / 4.0, this->body.getRadius() / 6.0);
    Point p5(this->body.getRadius() / 4.0, this->body.getRadius() / 6.0);
    Point p6(0.0, 0.0);

    incrementPropellerAngle();
    glTranslatef(this->body.getRadius() / 2.0, 0, 0.0);
    glRotatef(propellerAngle, 1.0, 0.0, 0.0);

    drawer.drawTriangle(p3, p2, p1, propellerColor);
    drawer.drawTriangle(p4, p5, p6, propellerColor);

    glPopMatrix();
}

void Airplane::drawCannon()
{
    glPushMatrix();

    Color color(0.0, 0.0, 0.0);

    glTranslatef(this->body.getRadius() * 0.9, 0.0, 0.0);
    glRotatef(-90 + calc.radiansToDegrees(cannonAngle), 0.0, 0.0, 1.0);
    drawer.drawRectangle(this->body.getRadius() / 5.0, this->body.getRadius() / 2.0, color);

    glPopMatrix();
}

GLfloat Airplane::calcMovement_x(GLfloat deltaIdleTime)
{
    return speedNorm * deltaIdleTime * cos(moveAngle);
}

GLfloat Airplane::calcMovement_y(GLfloat deltaIdleTime)
{
    return speedNorm * deltaIdleTime * sin(moveAngle);
}

void Airplane::move(GLfloat deltaIdleTime)
{
    updateTurnLeftAngle(deltaIdleTime);
    updateTurnRightAngle(deltaIdleTime);
    updateInclinationAngle(deltaIdleTime);

    dX += calcMovement_x(deltaIdleTime);
    dY -= calcMovement_y(deltaIdleTime);
}

void Airplane::updateTurningAngles(GLfloat deltaIdleTime)
{
    updateTurnLeftAngle(deltaIdleTime);
    updateTurnRightAngle(deltaIdleTime);
}

GLfloat Airplane::calcNextMovement_x(GLfloat deltaIdleTime, GLfloat nextMoveAngle)
{
    return speedNorm * deltaIdleTime * cos(nextMoveAngle);
}

GLfloat Airplane::calcNextMovement_y(GLfloat deltaIdleTime, GLfloat nextMoveAngle)
{
    return speedNorm * deltaIdleTime * sin(nextMoveAngle);
}

Point Airplane::getNextPosition(GLfloat deltaIdleTime)
{
    GLfloat nextMoveAngle = getNextMoveAngle(deltaIdleTime);
    Point nextPosition;

    nextPosition.setX(dX + calcNextMovement_x(deltaIdleTime, nextMoveAngle));
    nextPosition.setY(dY - calcNextMovement_y(deltaIdleTime, nextMoveAngle));

    return nextPosition;
}

bool Airplane::checkIntersection(Circle flightAreaBody, Circle enemyBody, GLfloat deltaIdleTime)
{
    Circle adjustedBody = Circle(this->getNextPosition(deltaIdleTime), this->body.getRadius());
    adjustedBody.setCenter_x(flightAreaBody.getCenter_x() + adjustedBody.getCenter_x());
    adjustedBody.setCenter_y(flightAreaBody.getCenter_y() + adjustedBody.getCenter_y());

    return adjustedBody.checkIntersection(enemyBody, this->drawer.getNumSegments());
}

bool Airplane::isInside(Circle circle, GLint moveDirection, GLfloat deltaIdleTime)
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

Circle Airplane::getAdjustedBody()
{
    Circle adjustedBody = this->body;
    adjustedBody.setCenter_x(adjustedBody.getCenter_x() - startPosition.getX() + this->dX);
    adjustedBody.setCenter_y(adjustedBody.getCenter_y() - startPosition.getY() + this->dY);

    return adjustedBody;
}

GLfloat Airplane::getNextMoveAngle(GLfloat deltaIdleTime)
{
    GLfloat nextAngle = moveAngle;

    if (isTurningLeft())
    {
        nextAngle += (M_PI / 2.0 * deltaIdleTime);
    }

    if (isTurningRight())
    {
        nextAngle -= (M_PI / 2.0 * deltaIdleTime);
    }

    return nextAngle;
}

void Airplane::updateTurnRightAngle(GLfloat deltaIdleTime)
{
    if (isTurningRight())
    {
        moveAngle -= M_PI / 2.0 * deltaIdleTime;
    }
}

void Airplane::updateTurnLeftAngle(GLfloat deltaIdleTime)
{
    if (isTurningLeft())
    {
        moveAngle += M_PI / 2.0 * deltaIdleTime;
    }
}

void Airplane::updateInclinationAngle(GLfloat deltaIdleTime)
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

void Airplane::reset()
{
    body.setRadius(initialRadius);
    dX = 0.0; //variação em X
    dY = 0.0; //variação em Y
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
    destroyed = false;
}

void Airplane::incrementSpeed()
{
    speedNorm += speedIncrement;
}

void Airplane::incrementSpeed(GLfloat speedIncrement)
{
    speedNorm += speedIncrement;
}

void Airplane::decrementSpeed()
{
    speedNorm -= speedIncrement;

    if (speedNorm < 0.0)
    {
        speedNorm = 0.0;
    }
}

void Airplane::decrementSpeed(GLfloat speedIncrement)
{
    speedNorm -= speedIncrement;

    if (speedNorm < 0.0)
    {
        speedNorm = 0.0;
    }
}

void Airplane::teleport()
{
    GLfloat x = dX;
    GLfloat y = dY;

    GLfloat alpha = atan2(y, x) * 180.0 / M_PI;
    GLfloat beta = (calc.degreesToRadians(this->inclinationAngle) - M_PI / 2.0) * 180.0 / M_PI;
    GLfloat theta = (-2.0 * (alpha - beta)) * M_PI / 180.0;

    this->dX = (x * cos(theta)) - (y * sin(theta));
    this->dY = (x * sin(theta)) + (y * cos(theta));
}

Point Airplane::getCurrentPositionAdjusted()
{
    Point currentPositionAdjusted;
    currentPositionAdjusted.setX(this->body.getCenter_x() + dX - this->startPosition.getX());
    currentPositionAdjusted.setY(this->body.getCenter_y() + dY - this->startPosition.getY());

    return currentPositionAdjusted;
}

Point Airplane::getPositionAdjusted(Point position)
{
    Point currentPositionAdjusted;
    currentPositionAdjusted.setX(this->body.getCenter_x() + position.getX() - this->startPosition.getX());
    currentPositionAdjusted.setY(this->body.getCenter_y() + position.getY() - this->startPosition.getY());

    return currentPositionAdjusted;
}

void Airplane::rotateCannon(GLfloat moviment, GLfloat deltaIdleTime)
{
    GLfloat nextCannonAngle = this->cannonAngle + moviment * 0.1 * deltaIdleTime;

    if (nextCannonAngle > M_PI / 4.0)
    {
        cannonAngle = M_PI / 4.0;
    }
    else if (nextCannonAngle < -M_PI / 4.0)
    {
        cannonAngle = -M_PI / 4.0;
    }
    else
    {
        cannonAngle = nextCannonAngle;
    }
}

Bullet *Airplane::shoot(GLfloat deltaIdleTime)
{
    GLfloat resultingAngle = calc.degreesToRadians(inclinationAngle) + cannonAngle;
    GLfloat bulletSpeed = speedNorm * bulletSpeedMultiplier;
    GLfloat bulletRadius = this->body.getRadius() / 8.0;
    Point bulletCoordinates;

    bulletCoordinates.setX(
        dX + body.getRadius() * cos(calc.degreesToRadians(inclinationAngle)) + this->body.getRadius() / 2.0 * cos(resultingAngle));
    bulletCoordinates.setY(
        dY + body.getRadius() * sin(calc.degreesToRadians(inclinationAngle)) + this->body.getRadius() / 2.0 * sin(resultingAngle));

    Point bulletBodyCoordinates = getPositionAdjusted(bulletCoordinates);

    return new Bullet(bulletBodyCoordinates, bulletRadius, bulletCoordinates, bulletSpeed, resultingAngle);
}