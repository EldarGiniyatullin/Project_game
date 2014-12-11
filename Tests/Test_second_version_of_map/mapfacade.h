#pragma once
#include <QWidget>
#include <QVector>
#include <QDebug>
#include "graphics_scene.h"
#include "map_square.h"

template <typename T>
class ObjectMap
{
public:
    ObjectMap(int xSize, int ySize) : xMapWidth(xSize), yMapHeight(ySize), table(QVector<QVector <T*> > (yMapHeight))
    {
        for (int i = 0; i < table.size(); i++)
        {
            table[i] = QVector <T*> (xMapWidth);
            for (int j = 0; j < table[i].size(); j++)
            {
 //------------- proplems with copying!!!--------------------------------------------------
                table[i][j] = nullptr;
            }
        }
    }
    const T& objectAt(int x, int y)
    {
        qDebug() << "passability at square number " << x << y;
        if (x >=0 && x <= xMapWidth && y >= 0 && y <= yMapHeight)
        return table[x][y];
    }

protected:
    QVector<QVector<T*> > table;
    int xMapWidth;
    int yMapHeight;
};


//тут может быть шаблон
class SurfaceMap
{
public:
//    SurfaceMap(); //can do problens with ui?
    SurfaceMap(int xSize, int ySize) : xMapWidth(xSize), yMapHeight(ySize), table(QVector<QVector <SurfaceObject*> > (xMapWidth))
    {
        for (int i = 0; i < table.size(); i++)
        {
            table[i] = QVector <SurfaceObject*> (yMapHeight);
            for (int j = 0; j < table[i].size(); j++)
            {
 //------------- proplems with copying!!!--------------------------------------------------
                table[i][j] = (((i + j) % 2) == 0 ? factory->clone(ROAD) : factory->clone(FIELD));
            }
        }
    }
    const SurfaceObject& objectAt(int x, int y)
    {
        if (x >=0 && x < xMapWidth && y >= 0 && y < yMapHeight)
        {
            if (table[x][y])
            {
                qDebug() << "objectAt square number " << x << " " << y;
                return *table[x][y];
            }
            else qDebug() << "error: nullptr square number " << x << " " << y;
        }
        else qDebug() << "error: incorrect square number " << x << " " << y;
    }

protected:
    SurfaceFactory *factory;
    int xMapWidth;
    int yMapHeight;
    QVector<QVector<SurfaceObject*> > table;
};


namespace Ui {
class MapFacade;
}

class MapFacade : public QWidget
{
    Q_OBJECT

public:

    //x and y - change!!!
    MapFacade(int xSquareNum, int ySquareNum, int squareSide, QWidget *parent = 0);
    ~MapFacade();
    bool checkPassabilityOfSquare(int xCoord, int yCoord);



//    Personage *personageAt(const QPointF &point)
//    {
//        QPoint tempPoint = toMapCoordinates(point);
//        return personageMap[tempPoint.x()][tempPoint.y()];
//    }

    QPoint toMapCoordinates(const QPointF &point)
    {
        return QPoint(xToMapCoordinates(point), yToMapCoordinates(point));
    }

    int xToMapCoordinates(const QPointF &point)
    {
        return (point.x() + (xWidth / 2)) / squareSize;
    }

    int yToMapCoordinates(const QPointF &point)
    {
        return (point.y() + (yHeight / 2))  / squareSize;
    }

    QPointF squareCenter(int x, int y)
    {
        return QPointF(squareSize * x + (squareSize / 2) + 1 - (xWidth / 2), squareSize * y +(squareSize / 2) + 1 - (yHeight / 2));
    }











protected:
    int xSquareNumber;
    int ySquareNumber;
    int squareSize;
    int xWidth;
    int yHeight;
//    ObjectMap personageMap;
//    ObjectMap buildingsMap;
//    ObjectMap propsMap;
    SurfaceMap *surMap;
    GraphicsScene *mapScene;
private:
    Ui::MapFacade *ui;
};
