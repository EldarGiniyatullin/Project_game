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

class MapObject
{
public:
    MapObject(GameObject object = GameObject()) : baseGameObject(object),
        objectPixmapItem(new QGraphicsPixmapItem(object.getPixmap()))
    {}
    GameObject baseGameObject;
    QGraphicsPixmapItem *objectPixmapItem;
};

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

class GraphicsScene
{
public:
    GraphicsScene( int height,  int width,  int square, QWidget *parent = 0)
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

