#include <stdio.h>
#include <cmath>
#include <iostream>
#include <string>

#include "circle.h"

using namespace std;

bool Circle::isPointInCircle(Point p)
{
    GLfloat d = sqrt(pow((p.getX() - center.getX()), 2) + pow((p.getY() - center.getY()), 2));

    if (d > radius)
    {
        return false;
    }

    return true;
}

bool Circle::isPointInCircle(GLfloat x, GLfloat y)
{
    return isPointInCircle(Point(x, y));
}

bool Circle::checkIntersection(Circle circle, GLint num_segments)
{
    for (GLint ii = 0; ii < num_segments; ii++)
    {
        GLfloat theta = 2.0f * 3.1415926f * GLfloat(ii) / GLfloat(num_segments); //get the current angle

        GLfloat x = circle.getRadius() * cosf(theta) + circle.getCenter_x(); //calculate the x component
        GLfloat y = circle.getRadius() * sinf(theta) + circle.getCenter_y(); //calculate the y component

        if (isPointInCircle(x, y))
        {
            return true;
        }
    }

    return false;
}

//Verifica se o circulo circle está dentro deste
bool Circle::isInside(Circle circle, GLint num_segments)
{
    for (GLint ii = 0; ii < num_segments; ii++)
    {
        GLfloat theta = 2.0f * 3.1415926f * GLfloat(ii) / GLfloat(num_segments); //get the current angle

        GLfloat x = circle.getRadius() * cosf(theta) + circle.getCenter_x(); //calculate the x component
        GLfloat y = circle.getRadius() * sinf(theta) + circle.getCenter_y(); //calculate the y component

        if (isPointInCircle(x, y) == false)
        {
            return false;
        }
    }

    return true;
}