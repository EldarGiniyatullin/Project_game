#pragma once

#include "map_object.h"

enum PropType {NULLOBJECT = 0, TREE_1, TREE_2};

class PropObject : public MapObject
{
public:
    PropObject()
        : MapObject(QPixmap("://No_image.png")),
          isPassable(true),
          type(TREE_1)
    {setDrawingPriority(0);}
    PropObject(QPixmap pixmap, int vertCorr, int horizCorr, PropType objType, bool isPass = true, qreal prioroty = 0)
        : MapObject(pixmap, vertCorr, horizCorr),
          isPassable(isPass),
          type(objType)
    {setDrawingPriority(prioroty);}
    PropObject(QPixmap pixmap, PropType objType,   bool isPass = true, qreal prioroty = 0)
        : MapObject(pixmap),
          isPassable(isPass),
          type(objType)
    {setDrawingPriority(prioroty);}
    PropObject(PixmapItem *pixItem, PropType objType,  bool isPass = true, qreal prioroty = 0)
        : MapObject(pixItem),
          isPassable(isPass),
          type(objType)
    {setDrawingPriority(prioroty);}
    PropObject(const PropObject& objectToCopy)
        : MapObject(objectToCopy),
          isPassable(objectToCopy.getIsPassable()),
          type(objectToCopy.getPropType())
    {setDrawingPriority(objectToCopy.getDrawingPriority());}
//    PropObject( PropObject *objectToCopy) : MapObject(*objectToCopy), isPassable(objectToCopy->getIsPassable()) {}
    ~PropObject()
    {

    }

    void setPassability(bool passability)
    {
        isPassable = passability;
    }

    bool getIsPassable() const
    {
        return isPassable;
    }

    PropType getPropType() const
    {
        return type;
    }

//    void setPos()
//    {
//    }

protected:
    bool isPassable;
    PropType type;
};

