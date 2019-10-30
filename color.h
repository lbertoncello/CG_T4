#ifndef COLOR_H
#define COLOR_H

#include <GL/glut.h>
#include <iostream>
#include <string>

using namespace std;

class Color
{
private:
    GLfloat r = 0;
    GLfloat g = 0;
    GLfloat b = 0;

public:
    Color() {}

    Color(GLfloat r, GLfloat g, GLfloat b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
    }

    Color(string colorName)
    {
        if (colorName == "red")
        {
            this->r = 1;
        }
        else if (colorName == string("green"))
        {
            this->g = 1;
        }
        else if (colorName == string("blue"))
        {
            this->b = 1;
        }
        else if (colorName == string("orange"))
        {
            this->r = 1;
            this->g = 0.65;
        }
    }

    GLfloat getR()
    {
        return r;
    }

    GLfloat getG()
    {
        return g;
    }

    GLfloat getB()
    {
        return b;
    }

    void setR(GLfloat r)
    {
        this->r = r;
    }

    void setG(GLfloat g)
    {
        this->g = g;
    }

    void setB(GLfloat b)
    {
        this->b = b;
    }
};

#endif