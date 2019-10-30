#ifndef AIRPORT_RUNWAY_H
#define AIRPORT_RUNWAY_H

#include "line.h"
#include "draw.h"
#include "calc.h"

class AirportRunway
{
    Line body;
    Line adjustedBody;
    GLfloat scalarMiddle;
    Draw drawer;
    Calc calc;

public:
    AirportRunway() {}

    AirportRunway(Line body)
    {
        this->body = body;
    }

    Line &getBody()
    {
        return body;
    }

    GLfloat getScalarMiddle()
    {
        return scalarMiddle;
    }

    void setBody(Line body)
    {
        this->body = body;
    }

    void setScalarMiddle(GLfloat scalarMiddle)
    {
        this->scalarMiddle = scalarMiddle;
    }

    Line getAdjustedBody() {
        return this->adjustedBody;
    }
    
    void setAdjustedBody(GLfloat coordinateCorrection_x, GLfloat coordinateCorrection_y);

    void draw();
    GLfloat calcInclinationAngle();
};

#endif