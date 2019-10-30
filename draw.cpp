#include "draw.h"

bool Draw::thereIsCircleMoving()
{
    if (currentCircleMoving == NULL)
    {
        return false;
    }

    return true;
}

void Draw::updateCurrentCircleMoving()
{
    currentCircleMoving->updateCenter(currentCenter);
}

void Draw::drawCircle(GLfloat cx, GLfloat cy, GLfloat r, GLint num_segments, Color color)
{
    glColor3f(color.getR(), color.getG(), color.getB());
    glBegin(GL_LINE_LOOP);

    for (GLint ii = 0; ii < num_segments; ii++)
    {
        GLfloat theta = 2.0f * 3.1415926f * GLfloat(ii) / GLfloat(num_segments); //get the current angle

        GLfloat x = r * cosf(theta); //calculate the x component
        GLfloat y = r * sinf(theta); //calculate the y component

        glVertex2f(x, y); //output vertex
    }
    glEnd();
}

void Draw::drawEllipse(GLfloat rx, GLfloat ry, Color color, GLint num_segments)
{
    GLfloat theta = 2 * 3.1415926 / GLfloat(num_segments);
    GLfloat c = cosf(theta); //precalculate the sine and cosine
    GLfloat s = sinf(theta);
    GLfloat t;

    GLfloat x = 1; //we start at angle = 0
    GLfloat y = 0;

    glColor3f(color.getR(), color.getG(), color.getB());

    glBegin(GL_TRIANGLE_FAN);
    for (GLint ii = 0; ii < num_segments; ii++)
    {
        //apply radius and offset
        glVertex2f(x * rx, y * ry); //output vertex

        //apply the rotation matrix
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }
    glEnd();
}

void Draw::drawFilledCircle(GLfloat x1, GLfloat y1, double radius, Color color)
{
    //filled circle
    GLfloat x2, y2;
    x1 = 0;
    y1 = 0;
    GLfloat angle;

    glColor3f(color.getR(), color.getG(), color.getB());

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x1, y1);

    for (angle = 1.0f; angle < 361.0f; angle += 0.2)
    {
        x2 = x1 + sin(angle) * radius;
        y2 = y1 + cos(angle) * radius;
        glVertex2f(x2, y2);
    }

    glEnd();
}

void Draw::drawRectangle(Point p1, Point p2, Point p3, Point p4, Color color)
{
    glColor3f(color.getR(), color.getG(), color.getB());
    glBegin(GL_POLYGON);
    glVertex3f(p1.getX(), p1.getY(), 0.0);
    glVertex3f(p2.getX(), p2.getY(), 0.0);
    glVertex3f(p3.getX(), p3.getY(), 0.0);
    glVertex3f(p4.getX(), p4.getY(), 0.0);
    glEnd();
}

void Draw::drawRectangle(GLfloat width, GLfloat height, Color color)
{
    glColor3f(color.getR(), color.getG(), color.getB());
    glBegin(GL_QUADS);
    glVertex3f(-width / 2.0, 0, 0.0);
    glVertex3f(width / 2.0, 0, 0.0);
    glVertex3f(width / 2.0, height, 0.0);
    glVertex3f(-width / 2.0, height, 0.0);
    glEnd();
}

void Draw::drawTriangle(Point p1, Point p2, Point p3, Color color)
{
    glColor3f(color.getR(), color.getG(), color.getB());

    glBegin(GL_TRIANGLES);
    glVertex3f(p1.getX(), p1.getY(), 0.0);
    glVertex3f(p2.getX(), p2.getY(), 0.0);
    glVertex3f(p3.getX(), p3.getY(), 0.0);
    glEnd();
}

void Draw::updateCurrentCenter(GLfloat x, GLfloat y, GLfloat x_window_size, GLfloat y_window_size)
{
    GLfloat center_x = x;
    GLfloat center_y = y_window_size - y;

    currentCenter.update(center_x, center_y);
}

bool Draw::checkIntersection(Circle circle)
{
    for (circle_it = circles.begin(); circle_it != circles.end(); circle_it++)
    {
        if (circle.checkIntersection(*circle_it, num_segments))
        {
            return true;
        }
    }

    return false;
}

void Draw::drawCircle(Circle circle)
{
    drawCircle(circle.getCenter_x(), circle.getCenter_y(), circle.getRadius(), num_segments, circle.getColor());
}

void Draw::drawEllipse(Circle circle)
{
    drawEllipse(circle.getRadius(), circle.getRadius() / 4, circle.getColor(), num_segments);
}

void Draw::drawEllipse(GLfloat radius, Color color)
{
    drawEllipse(radius, radius / 4, color, num_segments);
}

void Draw::drawCircle(Color color)
{
    drawCircle(currentCenter.getX(), currentCenter.getY(), radius, num_segments, color);
}

void Draw::drawFilledCircle(Color color)
{
    drawFilledCircle(currentCenter.getX(), currentCenter.getY(), radius, color);
}

void Draw::drawFilledCircle(Circle circle)
{
    drawFilledCircle(circle.getCenter_x(), circle.getCenter_y(), circle.getRadius(), circle.getColor());
}

void Draw::drawAllCircles(Color color)
{
    for (circle_it = circles.begin(); circle_it != circles.end(); circle_it++)
    {
        drawFilledCircle(circle_it->getCenter_x(), circle_it->getCenter_y(), circle_it->getRadius(), color);
    }
}

void Draw::drawAllCircles()
{
    for (circle_it = circles.begin(); circle_it != circles.end(); circle_it++)
    {
        drawFilledCircle(circle_it->getCenter_x(), circle_it->getCenter_y(), circle_it->getRadius(), circle_it->getColor());
    }
}

void Draw::chooseCircleToMove()
{
    for (circle_it = circles.begin(); circle_it != circles.end(); circle_it++)
    {
        if (circle_it->isPointInCircle(currentCenter.getX(), currentCenter.getY()))
        {
            circle_it->setMoving(true);
            currentCircleMoving = &(*circle_it);
            break;
        }
    }
}

void Draw::drawLine(Line line)
{
    glColor3f(line.getColor().getR(), line.getColor().getG(), line.getColor().getB());
    glPointSize(0.5);

    glBegin(GL_LINES);
    glVertex2d(line.getPoint1_x(), line.getPoint1_y());
    glVertex2d(line.getPoint2_x(), line.getPoint2_y());
    glEnd();
}

void Draw::drawLine(Point p1, Point p2, Color color)
{
    glColor3f(color.getR(), color.getG(), color.getB());
    glPointSize(0.5);

    glBegin(GL_LINES);
    glVertex2d(p1.getX(), p1.getY());
    glVertex2d(p2.getX(), p2.getY());
    glEnd();
}

void Draw::drawAllLines()
{
    for (line_it = lines.begin(); line_it != lines.end(); line_it++)
    {
        drawLine(*line_it);
    }
}

void Draw::drawGame()
{
}