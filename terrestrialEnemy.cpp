#include "terrestrialEnemy.h"

void TerrestrialEnemy::draw()
{
    if (!isDestroyed())
    {
        glPushMatrix();
        glTranslatef(dX, dY, 0.0);
        // drawer.drawFilledCircle(this->getBody());
        drawer.drawRectangle2(body.getRadius() * 1.44, body.getRadius() * 1.44, body.getColor());
        drawer.drawFilledCircle(body.getRadius() * 0.7, Color(0.3, 0.45, 0.7));
        glPopMatrix();
    }
}

Point TerrestrialEnemy::getCurrentPositionAdjusted()
{
    Point currentPositionAdjusted;
    currentPositionAdjusted.setX(this->body.getCenter_x() - startPosition.getX() + dX);
    currentPositionAdjusted.setY(this->body.getCenter_y() - startPosition.getY() + dY);

    return currentPositionAdjusted;
}

Circle TerrestrialEnemy::getAdjustedBody()
{
    return Circle(this->getCurrentPositionAdjusted(), this->body.getRadius());
}

void TerrestrialEnemy::reset() {
    destroyed = false;
}