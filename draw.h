#ifndef DRAW_H
#define DRAW_H

#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

#include "circle.h"
#include "line.h"

using namespace std;

class Draw
{
private:
    GLfloat PI = 3.14159;
    GLint num_segments = 300;
    GLfloat radius = 0.1;

    Point currentCenter;
    vector<Circle> circles;
    vector<Circle>::iterator circle_it;
    vector<Line> lines;
    vector<Line>::iterator line_it;
    Circle *currentCircleMoving = NULL;

    void drawCircle(GLfloat cx, GLfloat cy, GLfloat r, GLint num_segments, Color color);
    void drawFilledCircle(GLfloat x1, GLfloat y1, double radius, Color color);
    void drawEllipse(GLfloat rx, GLfloat ry, Color color, GLint num_segments);

public:
    Draw() {}

    GLint getNumSegments()
    {
        return num_segments;
    }

    GLfloat getRadius()
    {
        return radius;
    }

    Point &getCurrentCenter()
    {
        return currentCenter;
    }

    Circle *getCurrentCircleMoving()
    {
        currentCircleMoving;
    }

    void setRadius(GLfloat radius)
    {
        this->radius = radius;
    }

    void setCurrentCircleMoving(Circle *circle)
    {
        this->currentCircleMoving = circle;
    }

    void addCircle(Circle circle)
    {
        circles.push_back(circle);
    }

    void addLine(Line line)
    {
        lines.push_back(line);
    }

    void addCircleAtCurrentCenter();
    bool thereIsCircleMoving();
    void updateCurrentCircleMoving();
    void updateCurrentCenter(GLfloat x, GLfloat y, GLfloat x_window_size, GLfloat y_window_size);
    bool checkIntersection(Circle circle);
    void drawCircle(Color color);
    void drawCircle(Circle circle);
    void drawEllipse(Circle circle);
    void drawEllipse(GLfloat radius, Color color);
    void drawRectangle(GLfloat width, GLfloat height, Color color);
    void drawRectangle(Point p1, Point p2, Point p3, Point p4, Color color);
    void drawTriangle(Point p1, Point p2, Point p3, Color color);
    void drawFilledCircle(Color color);
    void drawFilledCircle(Circle circle);
    void drawAllCircles(Color color);
    void drawAllCircles();
    void drawLine(Line line);
    void drawLine(Point p1, Point p2, Color color);
    void drawAllLines();
    void drawGame();
    void chooseCircleToMove();
};

#endif