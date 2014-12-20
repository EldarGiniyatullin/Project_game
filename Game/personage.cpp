#include "personage.h"


void Personage::setPersPos(int xPos, int yPos)
{
    xCoord = xPos;
    yCoord = yPos;
}

Personage &Personage::operator=(const Personage &pers)
{
    Personage temp(pers);
    return temp;
}
