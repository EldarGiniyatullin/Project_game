#pragma once
#include <QWidget>
#include <QVector>
#include <QDebug>
#include <QMouseEvent>
#include "graphics_scene.h"
#include "surface_map.h"
#include "prop_map.h"
#include "personage.h"
#include "astarpoint.h"




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


    Personage *personageAt(QPoint point)
    {
        for (int i = 0; i < listOfPersonages.size(); i++)
        {
            if (listOfPersonages[i]->currentPos() == point)
            {
                qDebug() << "personage is";
                return listOfPersonages[i];
            }
        }
        qDebug() << "personage is not";
        return nullptr;
    }

    QPoint toMapCoordinates(const QPointF &point)
    {
        return QPoint(xToMapCoordinates(point), yToMapCoordinates(point));
    }

    qreal xToMapCoordinates(const QPointF &point)
    {
        return (point.x() + (xWidth / 2)) / squareSize;
    }

    qreal yToMapCoordinates(const QPointF &point)
    {
        return (point.y() + (yHeight / 2))  / squareSize;
    }

    QPointF squareCenter(int x, int y)
    {
        return QPointF(squareSize * x + (squareSize / 2) + 1 - (xWidth / 2), squareSize * y +(squareSize / 2) + 1 - (yHeight / 2));
    }

    QPointF squareCenter(QPoint point)
    {
        return squareCenter(point.x(), point.y());
    }

    void addPersonage(Personage *pers, int xCoord, int yCoord);
    void drawPersWay(Personage *pers);
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
    QList<Personage*> listOfPersonages;
    PersonageMaker persMaker;
    Personage *settedPers;
public slots:
    void buildWay(Personage* pers, QPoint point);
private:
    Ui::MapFacade *ui;

	AStarPoint *getPoint(QPoint point);
	AStarPoint *getPointFromCoord(QPoint coord);
	QMap <int, QMap <int, AStarPoint*> > AStarCells;
	bool pointExists(QPoint point);
};
