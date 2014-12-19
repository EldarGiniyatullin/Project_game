#include "personage.h"


void Personage::setPos(int xPos, int yPos)
{
    xCoord = xPos;
    yCoord = yPos;
}

Personage &Personage::operator=(const Personage &pers)
{
    Personage temp(pers);
    return temp;
}
