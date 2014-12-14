#include "personage_maker.h"


PersonageMaker::PersonageMaker(int squareSize)
{
    map.clear();
    QPixmap warrior("://first_personage.png");
    map.insert(WARRIOR, Personage(warrior, warrior.width() / (-2), (squareSize / 2) - warrior.height(), GREEN, WARRIOR));
}

PersonageMaker::~PersonageMaker()
{

}

Personage *PersonageMaker::makePers(Fraction frac, Speciality spec)
{
    Personage *newPers(new Personage(map.value(spec)));
    newPers->setPersFraction(frac);
    return newPers;
}
