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
int Personage::getCurrentSteps() const
{
    return currentSteps;
}

void Personage::setCurrentSteps(int value)
{
    currentSteps = value;
}
int Personage::getMaxSteps() const
{
    return maxSteps;
}

void Personage::setMaxSteps(int value)
{
    maxSteps = value;
}



int Personage::getHP()
{
    return hp;
}

void Personage::setHP(int hp)
{
    this->hp = hp;
}
