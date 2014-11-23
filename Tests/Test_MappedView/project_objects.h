#pragma once

#include <QPixmap>
#include <QGraphicsItem>

//примерно

//for save
class GameObject
{
    GameObject(QPixmap pixmap = QPixmap("://No_image.png"), bool isPassable = true)
        : objectPixmap(pixmap), isPassable(isPassable) {}
    QPixmap objectPixmap;
    bool isPassable;
    const QPixmap & getPixmap()
    {
        return objectPixmap;
    }
    bool isPassable()
    {
        return isPassable;
    }

};

class TreeObject : public GameObject
{
public:
    TreeObject() : GameObject(QPixmap("://Little_tree.png"), false) {}
};

// after conversion
//      ||
//      ||
//      \/
//for map
class MapObject
{
public:
    MapObject(GameObject object) : baseGameObject(object),
        objectPixmapItem(new QGraphicsPixmapItem(object.getPixmap()))
    {}
    GameObject baseGameObject;
    QGraphicsPixmapItem *objectPixmapItem;
};
