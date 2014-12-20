#pragma once

#include <QMap>

#include "personage.h"


//it needs better realization
class PersonageMaker
{
public:
    PersonageMaker(int squareSize);
    ~PersonageMaker();
    Personage *makePers(Fraction frac, Speciality spec);
protected:
    QMap<Fraction, Personage> map;
};






