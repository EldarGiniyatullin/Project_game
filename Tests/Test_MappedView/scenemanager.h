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

#include "mapobject.h"
#include "scenetable.h"
#include "graphicsscene.h"







//паттерн
class SceneManager
{
public:
    SceneManager( int height,  int width,  int square, QWidget *parent = 0)
        : manHeight(height), manWidth(width), manSquare(square)
    {
        grScene = new GraphicsScene(height, width, square, parent);
        table = new SceneTable(height, width, square);
        table->fillTable(TreeObject());
        for (int i = 0; i < table->sceneHeightSize; i++)
            for (int j = 0; j < table->sceneWidthSize; j++)
            {
                grScene->scene->addItem(table->row[i][j]->objectPixmapItem);
                table->row[i][j]->objectPixmapItem->setPos(table->squareCenter(i, j));
            }

    }

    void addItem(const QPoint &point, MapObject *object = new MapObject())
    {
        QPointF floatPoint = grScene->view->mapToScene(point).toPoint();
        qDebug() << "mapToScene = " << grScene->view->mapToScene(point).toPoint();
        int x = table->toMapCoordinates(floatPoint).x();
        int y = table->toMapCoordinates(floatPoint).y();
        //        int x = table->xToMapCoordinates(grScene->view->mapToScene(point).toPoint());
        //        int y = table->yToMapCoordinates(grScene->view->mapToScene(point).toPoint());
        qDebug() << "x map = " << x;
        qDebug() << "y map = " << y;
        if ((x >=0) && (x < table->sceneHeightSize) && (y >=0) && (y < table->sceneWidthSize))
        {
            grScene->scene->removeItem(table->row[x][y]->objectPixmapItem);
            delete table->row[x][y];
            table->row[x][y] = object;
            /*QGraphicsPixmapItem *item = */grScene->scene->addItem(object->objectPixmapItem);
            object->objectPixmapItem->setPos(table->squareCenter(x, y));
            qDebug() << object->objectPixmapItem->pixmap().height();
            qDebug() << object->objectPixmapItem->pixmap().width() / 2;
        }
    }

    ~SceneManager();
    GraphicsScene *grScene;
    SceneTable * table;
    int manHeight;
    int manWidth;
    int manSquare;
};






//class SceneTable
//{
//public:
//    SceneTable(unsigned int x = 3, unsigned int sceneX, unsigned int sceneY):
//        x(x), sceneX(sceneX), sceneY(sceneY), row(new **QGraphicsItem[sceneX / x])
//    {
//        for (int i = 0; i < (sceneX / x); i++)
//        {
//            row[i] = new *QGraphicsItem[sceneY / x];
//            for (int j = 0; j < sceneY / x; j++)
//                row[i][j] = new QGraphicsItem;
//        }
//    }
//    QGraphicsItem ***row;

//protected:
//    unsigned int x;
//    unsigned int sceneX;
//    unsigned int sceneY;
//};

