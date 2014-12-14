#pragma once

#include <QList>
#include <QString>
#include "mapfacade.h"

class MapFacadeSaveObject
{
public:
    int xSquareNumber;
    int ySquareNumber;
    int numberOfPersonages;
    QString saveName;
    struct SavedPersonage
    {
        SavedPersonage(Fraction fraction, Speciality speciality)
        {
            frac = fraction;
            spec = speciality;
        }

        Fraction frac;
        Speciality spec;
    };
    QList <SavedPersonage> personages;
    QList <PropType> props;
    QList <SurfaceType> surfaces;
};
