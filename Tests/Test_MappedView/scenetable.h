#pragma once

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <cmath>
#include <QPoint>
#include <QVector>
#include <QDebug>
#include <QtMath>
#include <QPointF>
#include "graphicsscene.h"


class MapObject
{
public:
    MapObject(QPixmap pixmap = QPixmap("://No_image.png"), bool isPassable = true) :
        objectItem(new QGraphicsPixmapItem(pixmap)), isPassable(isPassable) {}

    QGraphicsPixmapItem *objectItem;

    bool isPassable;
    //Character *character;
};

class SceneTable
{
public:
    SceneTable(unsigned int height, unsigned int width, unsigned int square, GraphicsScene *parentScene) :
        sceneHeight(height), sceneWidth(width), squareSize(square), parentScene(parentScene)

    {
        //создание таблицы
        row = QVector<QVector <MapObject*> > (height / square);
        for (int i = 0; i < row.size(); i++)
        {
            row[i] = QVector <MapObject*> (width / square);
            for (int j = 0; j < row[i].size(); j++)
            {
                //тут предполагаются изменения
                row[i][j] = new MapObject();
                parentScene->scene->addItem(row[i][j]->objectItem);
            }
        }
    }
    GraphicsScene *parentScene;
    unsigned int sceneHeight;
    unsigned int sceneWidth;
    unsigned int squareSize;

    MapObject *objectAt(const QPoint &point)
    {
        QPoint tempPoint = toMapCoordinates(point);
        return row[tempPoint.x()][tempPoint.y()];
    }

    QPoint toMapCoordinates(const QPoint &point)
    {
        return QPoint(xToMapCoordinates(point), yToMapCoordinates(point));
    }

    int xToMapCoordinates(const QPoint &point)
    {
        return (point.x() + sceneHeight / 2) / squareSize;
    }

    int yToMapCoordinates(const QPoint &point)
    {
        return (point.y() + sceneWidth / 2) / squareSize;
    }

private:
    QVector<QVector<MapObject*> > row;
};





class TreeObject : public MapObject
{
public:
    TreeObject() : MapObject(QPixmap("://Little_tree.png"), false) {}
};
