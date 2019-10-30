#ifndef CALC_H
#define CALC_H

#include <GL/glut.h>
#include <vector>

#include "point.h"

using namespace std;

class Calc
{
public:
    Calc() {}

    GLfloat calcAccelerationRequired(GLfloat initialPosition, GLfloat finalPosition, GLfloat initialSpeed, GLfloat time);
    vector<GLfloat> calcAccelerationRequired(Point initialPosition, Point finalPosition, vector<GLfloat> initialSpeed, GLfloat time);
    GLfloat calcTimeRequired(GLfloat initialSpeed, GLfloat finalSpeed, GLfloat acceleration);
    GLfloat calcPositionRequired(GLfloat finalPosition, GLfloat acceleration, GLfloat time);
    GLfloat calcCurrentPositionVariation(GLfloat initialPosition, GLfloat acceleration, GLfloat initialSpeed, GLfloat time);
    Point calcCurrentPositionVariation(Point initialPosition, vector<GLfloat> acceleration, vector<GLfloat> initialSpeed, GLfloat time);
    GLfloat calcInitialSpeedRequired(GLfloat finalSpeed, GLfloat acceleration, GLfloat initialPosition, GLfloat finalPosition);
    GLfloat calcFinalSpeedRequired(GLfloat initialSpeed, GLfloat acceleration, GLfloat time);
    vector<GLfloat> calcFinalSpeedRequired(vector<GLfloat> initialSpeed, vector<GLfloat> acceleration, GLfloat time);
    GLfloat euclideanDistance(GLint x1, GLint y1, GLint x2, GLint y2);
    GLfloat euclideanDistance(Point point1, Point point2);
    GLfloat norm(vector<GLfloat> v);
    vector<GLfloat> zerosVector(GLint numOfDimensions);
    GLfloat radiansToDegrees(GLfloat radians);
    GLfloat degreesToRadians(GLfloat degrees);
};

#endif