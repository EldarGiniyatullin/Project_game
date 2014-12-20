#pragma once

#include <QMap>

#include "surface_object.h"

class SurfaceFactory
{
public:
    SurfaceFactory()
    //add parameter squareSize for resizing the rect
    {
        map.clear();
        map.insert(FIELD, SurfaceObject(QPixmap("://field.png"), FIELD, true));
        map.insert(ROAD, SurfaceObject(QPixmap("://road.png"), ROAD, true));
        map.insert(WATER, SurfaceObject(QPixmap("://water.png"), WATER, false));
        map.insert(ROCKS, SurfaceObject(QPixmap("://rocks.png"), ROCKS, false));
        map.insert(SWAMP, SurfaceObject(QPixmap("://swamp.png"), SWAMP, false));
        currentType = FIELD;
    }


    SurfaceObject *clone(SurfaceType type)
    {
        return new SurfaceObject(map.value(type));
    }

    SurfaceObject *clone()
    {
        return clone(currentType);
    }

    void setType (SurfaceType type)
    {
        currentType = type;
    }

    SurfaceType currentType;
protected:
    QMap<SurfaceType, SurfaceObject> map;
};
