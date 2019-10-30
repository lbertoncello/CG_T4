#include "calc.h"

#include <cmath>

using namespace std;

GLfloat Calc::euclideanDistance(GLint x1, GLint y1, GLint x2, GLint y2)
{
    // Calculating distance
    return sqrt(pow(x2 - x1, 2) +
                pow(y2 - y1, 2) * 1.0);
}

GLfloat Calc::norm(vector<GLfloat> v)
{
    GLfloat sum = 0;

    for (vector<GLfloat>::iterator it = v.begin(); it != v.end(); ++it)
    {
        sum += (*it * *it);
    }

    return sqrt(sum);
}

GLfloat Calc::euclideanDistance(Point point1, Point point2)
{
    return euclideanDistance(point1.getX(), point1.getY(), point2.getX(), point2.getY());
}

GLfloat Calc::calcAccelerationRequired(GLfloat initialPosition, GLfloat finalPosition, GLfloat initialSpeed, GLfloat time)
{
    return 2 * (finalPosition - initialPosition - initialSpeed * time) / (time * time);
}

GLfloat Calc::calcCurrentPositionVariation(GLfloat initialPosition, GLfloat acceleration, GLfloat initialSpeed, GLfloat time)
{
    return (initialSpeed * time + (acceleration * pow(time, 2)) / 2);
}

vector<GLfloat> Calc::calcAccelerationRequired(Point initialPosition, Point finalPosition, vector<GLfloat> initialSpeed, GLfloat time)
{
    vector<GLfloat> acceleration;

    GLfloat acceleration_x = calcAccelerationRequired(initialPosition.getX(), finalPosition.getX(), initialSpeed[0], time);
    GLfloat acceleration_y = calcAccelerationRequired(initialPosition.getY(), finalPosition.getY(), initialSpeed[1], time);

    acceleration.push_back(acceleration_x);
    acceleration.push_back(acceleration_y);

    return acceleration;
}

GLfloat Calc::calcTimeRequired(GLfloat initialSpeed, GLfloat finalSpeed, GLfloat acceleration)
{
    return (finalSpeed - initialSpeed) / acceleration;
}

Point Calc::calcCurrentPositionVariation(Point initialPosition, vector<GLfloat> acceleration, vector<GLfloat> initialSpeed, GLfloat time)
{
    Point currentPosition;

    GLfloat currentPosition_x = calcCurrentPositionVariation(initialPosition.getX(), acceleration[0], initialSpeed[0], time);
    GLfloat currentPosition_y = calcCurrentPositionVariation(initialPosition.getY(), acceleration[1], initialSpeed[1], time);

    currentPosition.setX(currentPosition_x);
    currentPosition.setY(currentPosition_y);

    return currentPosition;
}

GLfloat Calc::calcFinalSpeedRequired(GLfloat initialSpeed, GLfloat acceleration, GLfloat time)
{
    return initialSpeed + acceleration * time;
}

vector<GLfloat> Calc::calcFinalSpeedRequired(vector<GLfloat> initialSpeed, vector<GLfloat> acceleration, GLfloat time)
{
    vector<GLfloat> finalSpeed;

    finalSpeed.push_back(calcFinalSpeedRequired(initialSpeed[0], acceleration[0], time));
    finalSpeed.push_back(calcFinalSpeedRequired(initialSpeed[1], acceleration[1], time));

    return finalSpeed;
}

GLfloat Calc::calcInitialSpeedRequired(GLfloat finalSpeed, GLfloat acceleration, GLfloat initialPosition, GLfloat finalPosition)
{
    return sqrt(pow(finalSpeed, 2) - 2 * acceleration * (finalPosition - initialPosition));
}

GLfloat Calc::radiansToDegrees(GLfloat radians)
{
    return radians * (180.0 / 3.141592653589793238463);
}

vector<GLfloat> Calc::zerosVector(GLint numOfDimensions)
{
    vector<GLfloat> zeros;

    for (GLint i = 0; i < numOfDimensions; i++)
    {
        zeros.push_back(0);
    }

    return zeros;
}

GLfloat Calc::degreesToRadians(GLfloat degrees)
{
    return 2 * M_PI * (degrees / 360.0);
}