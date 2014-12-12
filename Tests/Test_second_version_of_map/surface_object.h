#pragma once

#include <QPixmap>
#include <QMap>
#include "map_object.h"

enum SurfaceType {NOIMAGE = 0, FIELD, ROAD, WATER, ROCKS, /*SAND, BURNED,*/ SWAMP};

class SurfaceObject : public MapObject
{
public:
    SurfaceObject()
        : MapObject(QPixmap("://No_image.png")),
          isPassable(true),
          type(NOIMAGE)
    {setDrawingPriority(0);}
    SurfaceObject(QPixmap pixmap, int vert, int horiz, SurfaceType objType, bool isPass = true)
        : MapObject(pixmap, vert, horiz),
          isPassable(isPass),
          type(objType)
    {setDrawingPriority(0);}
    SurfaceObject(QPixmap pixmap, SurfaceType objType, bool isPass = true)
        : MapObject(pixmap),
          isPassable(isPass),
          type(objType)
    {setDrawingPriority(0);}
    SurfaceObject(PixmapItem *pixItem, SurfaceType objType, bool isPass = true)
        : MapObject(pixItem),
          isPassable(isPass),
          type(objType)
    {setDrawingPriority(0);}
    SurfaceObject(const SurfaceObject& objectToCopy)
        : MapObject(objectToCopy),
          isPassable(objectToCopy.getIsPassable()),
          type(objectToCopy.getSurfaceType())
    {setDrawingPriority(0);}
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

    SurfaceType getSurfaceType() const
    {
        return type;
    }

protected:
    bool isPassable;
    SurfaceType type;
};




class SurfaceFactory
{
public:
    SurfaceFactory()
    //add parameter squareSize for resizing the rect
    {
        map = new QMap<SurfaceType, SurfaceObject>;
        map->clear();
        map->insert(FIELD, SurfaceObject(QPixmap("://field.png"), FIELD, true));
        map->insert(ROAD, SurfaceObject(QPixmap("://road.png"), ROAD, true));
        map->insert(WATER, SurfaceObject(QPixmap("://water.png"), WATER, false));
        map->insert(ROCKS, SurfaceObject(QPixmap("://rocks.png"), ROCKS, false));
        map->insert(SWAMP, SurfaceObject(QPixmap("://swamp.png"), SWAMP, false));
        currentType = FIELD;
    }


    SurfaceObject *clone(SurfaceType type)
    {
        SurfaceObject *newObj(new SurfaceObject(map->value(type)));
        // и протестировать оптимизацию-обобщение
        return newObj;
    }

    SurfaceObject *clone()
    {
        return clone(currentType);
    }

    void setType (SurfaceType type)
    {
        currentType = type;
    }

protected:
    QMap<SurfaceType, SurfaceObject> *map;
    SurfaceType currentType;
};
