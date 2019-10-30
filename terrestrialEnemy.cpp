#include "terrestrialEnemy.h"

void TerrestrialEnemy::draw()
{
    drawer.drawFilledCircle(this->getBody());
}