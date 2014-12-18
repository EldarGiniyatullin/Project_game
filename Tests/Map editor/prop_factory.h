#pragma once

#include <QMap>

#include "prop_object.h"


class PropFactory
{
public:
    PropFactory()
    //add parameter squareSize for resizing the rect
    {
        map.clear();
        QPixmap  tree1("://tree_1.png");
        QPixmap  tree2("://tree_2.png");
        map.insert(TREE_1, PropObject(tree1, tree1.width() / (-2), tree1.height() * (-1), TREE_1, false));
        map.insert(TREE_2, PropObject(tree2, tree2.width() / (-2), tree2.height() * (-1), TREE_2, false));
        currentType = TREE_1;
    }
    ~PropFactory()
    {
    }

    PropObject *clone(PropType type);
    PropObject *clone(PropType type, qreal priority);
    PropObject *clone(qreal priority);
    PropObject *clone();

    void setType (PropType type)
    {
        currentType = type;
    }

    PropType currentType;
protected:
    QMap<PropType, PropObject> map;
};
