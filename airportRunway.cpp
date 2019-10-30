#include "airportRunway.h"

void AirportRunway::setAdjustedBody(GLfloat coordinateCorrection_x, GLfloat coordinateCorrection_y)
{
    Point p1(-coordinateCorrection_x + this->getBody().getPoint1_x(), -coordinateCorrection_y + this->getBody().getPoint1_y());
    Point p2(-coordinateCorrection_x + this->getBody().getPoint2_x(), -coordinateCorrection_y + this->getBody().getPoint2_y());

    this->adjustedBody = Line(p1, p2);
}

void AirportRunway::draw()
{
    drawer.drawLine(this->adjustedBody);
}

GLfloat AirportRunway::calcInclinationAngle()
{
    return calc.radiansToDegrees(
        atan2f(
            body.getPoint2_y() - body.getPoint1_y(),
            body.getPoint2_x() - body.getPoint1_x()));
}
