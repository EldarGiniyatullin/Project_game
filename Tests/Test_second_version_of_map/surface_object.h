#pragma once

#include <QPixmap>
#include <QMap>
#include "map_object.h"

class SurfaceObject : public MapObject
{
public:
    SurfaceObject() : MapObject(QPixmap("://No_image.png")), isPassable(true) {}
    SurfaceObject(QPixmap pixmap, int vert, int horiz, bool isPass = true) : MapObject(pixmap, vert, horiz), isPassable(isPass) {}
    SurfaceObject(QPixmap pixmap, bool isPass = true) : MapObject(pixmap), isPassable(isPass) {}
    SurfaceObject(PixmapItem *pixItem, bool isPass = true) : MapObject(pixItem), isPassable(isPass) {}
    SurfaceObject(const SurfaceObject& objectToCopy) : MapObject(objectToCopy), isPassable(objectToCopy.getIsPassable()) {}
//    SurfaceObject( SurfaceObject *objectToCopy) : MapObject(*objectToCopy), isPassable(objectToCopy->getIsPassable()) {}
//    ~SurfaceObject();
    void setPassability(bool passability)
    {
        isPassable = passability;
    }

    bool getIsPassable() const
    {
        return isPassable;
    }

protected:
    bool isPassable;
};


enum SurfaceType {FIELD = 1, ROAD, CROSS, NOIMAGE, WATER, ROCKS, SAND, BURNED};


class SurfaceFactory
{
public:
    SurfaceFactory()
    //add parameter squareSize for resizing the rect
    {
        map = new QMap<SurfaceType, SurfaceObject>;
        map->clear();
        map->insert(FIELD, SurfaceObject(QPixmap("://field.png"), true));
        map->insert(ROAD, SurfaceObject(QPixmap("://road.png"), true));
        map->insert(CROSS, SurfaceObject(QPixmap("://Cross.png"), true));
        map->insert(NOIMAGE, SurfaceObject(QPixmap("://No_image.png"), true));
    }

    SurfaceObject *clone(SurfaceType typeOfSurface)
    {
//        SurfaceObject *newObj(new SurfaceObject(map->value(typeOfSurface)));
        // и протестировать оптимизацию-обобщение
        SurfaceObject *newObj;
        switch(typeOfSurface)
        {
            case FIELD : newObj = new SurfaceObject(QPixmap("://field.png"), true);
        break;
            case ROAD : newObj = new SurfaceObject(QPixmap("://road.png"), true);
        break;
        }

        return newObj;
    }
protected:
    QMap<SurfaceType, SurfaceObject> *map;
};

