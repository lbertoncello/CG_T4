#ifndef FLIGHT_AREA_H
#define FLIGHT_AREA_H

#include "circle.h"
#include "draw.h"

class FlightArea
{
    Circle area;
    Draw drawer;

public:
    FlightArea() {}

    FlightArea(Circle circle)
    {
        this->area = circle;
    }

    Circle &getArea()
    {
        return area;
    }

    void setArea(Circle area)
    {
        this->area = area;
    }

    void draw();
};

#endif