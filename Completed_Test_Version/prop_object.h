#pragma once

#include "map_object.h"

enum PropType {TREE_1 = 1, TREE_2};

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
//    ~PropObject();
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

protected:
    bool isPassable;
    PropType type;
};


class PropFactory
{
public:
    PropFactory()
    //add parameter squareSize for resizing the rect
    {
        map = new QMap<PropType, PropObject>;
        map->clear();
        QPixmap  tree1("://tree_1.png");
        QPixmap  tree2("://tree_2.png");
        map->insert(TREE_1, PropObject(tree1, tree1.width() / (-2), tree1.height() * (-1), TREE_1, false));
        map->insert(TREE_2, PropObject(tree2, tree2.width() / (-2), tree2.height() * (-1), TREE_2, false));
        currentType = TREE_1;
    }


    PropObject *clone(PropType type)
    {
        PropObject *newObj(new PropObject(map->value(type)));
        return newObj;
    }
    PropObject *clone(PropType type, qreal priority)
    {
        PropObject *newObj(this->clone(type));
        newObj->setDrawingPriority(priority);
        return newObj;
    }
    PropObject *clone(qreal priority)
    {
        PropObject *newObj(this->clone());
        newObj->setDrawingPriority(priority);
        return newObj;
    }

    PropObject *clone()
    {
        return clone(currentType);
    }

    void setType (PropType type)
    {
        currentType = type;
    }

protected:
    QMap<PropType, PropObject> *map;
    PropType currentType;
};
