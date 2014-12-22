#include "personage_maker.h"


PersonageMaker::PersonageMaker(int squareSize)
{
    map.clear();
    QPixmap warriorRed("://first_personage.png");
    QPixmap warriorBlue("://blue_personage.png");
    map.insert(RED, Personage(warriorRed, warriorRed.width() / (-2), (squareSize / 2) - warriorRed.height(), RED, WARRIOR, 10));
    map.insert(BLUE, Personage(warriorBlue, warriorBlue.width() / (-2), (squareSize / 2) - warriorBlue.height(), BLUE, WARRIOR, 10));
}

PersonageMaker::~PersonageMaker()
{

}

Personage *PersonageMaker::makePers(Fraction frac, Speciality spec)
{
    Personage *newPers(new Personage(map.value(frac)));
    newPers->setPersFraction(frac);
    return newPers;
}
