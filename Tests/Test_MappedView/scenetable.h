#pragma once

#include <QPoint>
#include <QVector>
#include "mapobject.h"

class SceneTable
{
public:
    SceneTable( int height,  int width,  int square) :
        sceneHeight(height), sceneWidth(width), squareSize(square),
        sceneHeightSize(height / square), sceneWidthSize(width / square)

    {
        //создание таблицы
        row = QVector<QVector <MapObject*> > (sceneHeightSize);
        for (int i = 0; i < row.size(); i++)
        {
            row[i] = QVector <MapObject*> (sceneWidthSize);
            for (int j = 0; j < row[i].size(); j++)
            {
                row[i][j] = nullptr;
            }
        }
    }
    int sceneHeightSize;
    int sceneWidthSize;
    int sceneHeight;
    int sceneWidth;
    int squareSize;


    void fillTable(GameObject object)
    {
        for (int i = 0; i < sceneHeightSize; i++)
            for (int j = 0; j < sceneWidthSize; j++)
                row[i][j] = new MapObject(TreeObject());
    }

    MapObject *objectAt(const QPointF &point)
    {
        QPoint tempPoint = toMapCoordinates(point);
        return row[tempPoint.x()][tempPoint.y()];
    }

    QPoint toMapCoordinates(const QPointF &point)
    {
        return QPoint(xToMapCoordinates(point), yToMapCoordinates(point));
    }

    int xToMapCoordinates(const QPointF &point)
    {
        return (point.x() + (sceneHeight / 2)) / squareSize;
    }

    int yToMapCoordinates(const QPointF &point)
    {
        return (point.y() + (sceneWidth / 2))  / squareSize;
    }

    //    int xToMap(const QPoint &point)
    //    {
    //        return point.x() / sceneHeightSize;
    //    }

    //    int yToMap(const QPoint &point)
    //    {
    //        point.y() / sceneWidthSize;
    //    }

    QPointF squareCenter(int x, int y)
    {
        return QPointF(squareSize * x + (squareSize / 2) + 1 - (sceneHeight / 2), squareSize * y +(squareSize / 2) + 1 - (sceneWidth / 2));
    }

    QVector<QVector<MapObject*> > row;
};

