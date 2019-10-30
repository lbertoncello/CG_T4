#ifndef CIRCLE_H
#define CIRCLE_H

#include <iostream>
#include <GL/glut.h>

#include "point.h"
#include "color.h"

class Circle
{
private:
    GLint id;
    Point center;
    GLfloat radius;
    Color color;
    bool moving = false;
    bool terrestrial = false;
    bool mainCircle = false;

public:
    Circle() {}

    Circle(Point center, GLfloat radius)
    {
        this->center = center;
        this->radius = radius;
    }

    Circle(Point center, GLfloat radius, Color color)
    {
        this->center = center;
        this->radius = radius;
        this->color = color;
    }

    Circle(GLint id, Point center, GLfloat radius)
    {
        this->id = id;
        this->center = center;
        this->radius = radius;
    }

    Circle(GLfloat center_x, GLfloat center_y, GLfloat radius)
    {
        this->center.setX(center_x);
        this->center.setY(center_y);
        this->radius = radius;
    }

    Circle(GLint id, GLfloat center_x, GLfloat center_y, GLfloat radius)
    {
        this->id = id;
        this->center.setX(center_x);
        this->center.setY(center_y);
        this->radius = radius;
    }

    GLint getId()
    {
        return id;
    }

    Point getCenter() {
        return center;
    }

    GLfloat getCenter_x()
    {
        return center.getX();
    }

    GLfloat getCenter_y()
    {
        return center.getY();
    }

    GLfloat getRadius()
    {
        return radius;
    }

    Color& getColor()
    {
        return color;
    }

    bool isMoving()
    {
        return moving;
    }

    bool isTerrestrial()
    {
        return terrestrial;
    }

    bool isMainCircle()
    {
        return mainCircle;
    }

    void setId(GLint id)
    {
        this->id = id;
    }

    void setCenter_x(GLfloat center_x)
    {
        this->center.setX(center_x);
    }

    void setCenter_y(GLfloat center_y)
    {
        this->center.setY(center_y);
    }

    void setRadius(GLfloat radius)
    {
        this->radius = radius;
    }

    void setColor(Color color)
    {
        this->color = color;
    }

    void setMoving(bool moving)
    {
        this->moving = moving;
    }

    void setTerrestrial(bool terrestrial)
    {
        this->terrestrial = terrestrial;
    }

    void setMainCircle(bool mainCircle)
    {
        this->mainCircle = mainCircle;
    }

    void updateCenter(Point p)
    {
        this->center.setX(p.getX());
        this->center.setY(p.getY());
    }

    void updateCenter(GLfloat x, GLfloat y)
    {
        this->center.setX(x);
        this->center.setY(y);
    }

    bool isPointInCircle(Point p);
    bool isPointInCircle(GLfloat x, GLfloat y);
    bool checkIntersection(Circle circle, GLint num_segments);
    bool isInside(Circle circle, GLint num_segments);
};

#endif