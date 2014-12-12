#pragma once
#include <QWidget>
#include <QVector>
#include <QDebug>
#include <QMouseEvent>
#include "graphics_scene.h"
#include "surface_map.h"
#include "prop_map.h"
#include "personage.h"





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
    bool checkPassabilityOfSquare(QPoint squarePoint);


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

    void addPersonage(Personage *pers);
    void mousePressEvent(QMouseEvent *event);
protected:
    int xSquareNumber;
    int ySquareNumber;
    int squareSize;
    int xWidth;
    int yHeight;
//    ObjectMap personageMap;
//    ObjectMap buildingsMap;
    SurfaceMap *surMap;
    PropMap *prMap;
    GraphicsScene *mapScene;
public slots:
    void buildWay(Personage* pers, QPoint point);
private:
    Ui::MapFacade *ui;
};
