#pragma once

#include <QGraphicsView>

#include "mapobject.h"
#include "scenetable.h"

class GraphicsScene
{
public:
    GraphicsScene(int height, int width,  int square, QWidget *parent = 0)
    {
        scene = new QGraphicsScene();
        view = new QGraphicsView(scene, parent);
        //        int halfHeight = height / (-2);
        //        int halfWidth = width / (-2);
        table = new SceneTable(height, width, square);
        //        for (int i = 0; i < height / square; i++)
        //            for (int j = 0; j < width / square; j++)
        //            {
        //                this->addItem(QPoint(i, j), table->row[i][j]);
        //            }
        view->setFixedSize(height, width);
    }
    QGraphicsView *view;
    QGraphicsScene *scene;
    SceneTable *table;
    //    void addItem(QPoint point, MapObject *object = new MapObject)
    //    {


    ////        qDebug() <<
    ////        QGraphicsPixmapItem *item = scene->addPixmap(object->objectItem->pixmap());
    ////        delete table->objectAt(point);
    ////        table->objectAt(point) = object;
    //    }
};
