#pragma once

//#include <QPixmap>
#include <QGraphicsPixmapItem>

class GameObject
{
public:
    GameObject(QPixmap pixmap = QPixmap("://No_image.png"), bool isPassable = true)
        : objectPixmap(pixmap), isObjectPassable(isPassable) {}
    QPixmap objectPixmap;
    bool isObjectPassable;
    const QPixmap & getPixmap()
    {
        return objectPixmap;
    }
    bool isPassable()
    {
        return isObjectPassable;
    }

};

class TreeObject : public GameObject
{
public:
    TreeObject() : GameObject(QPixmap("://Little_tree.png"), false) {}
};

class PixmapItem : public QGraphicsPixmapItem
{

};

class MapObject
{
public:
    MapObject(GameObject object = GameObject()) : baseGameObject(object),
        objectPixmapItem(new QGraphicsPixmapItem(object.getPixmap()))
    {}
    GameObject baseGameObject;
    QGraphicsPixmapItem *objectPixmapItem;

    bool isCenter;
};
