#pragma once

#include <QThread>
#include <QKeyEvent>
#include <cmath>
#include <QTimer>
#include <QWidget>
#include <QDebug>
#include <QMouseEvent>

#include "graphics_scene.h"
#include "surface_map.h"
#include "prop_map.h"
#include "personage.h"
#include "astarpoint.h"
#include "personage_maker.h"


namespace Ui {
class MapFacade;
}

class MapFacade : public QWidget
{
    Q_OBJECT

public:
    MapFacade(int xSquareNum, int ySquareNum, int squareSide, QWidget *parent = 0);
    ~MapFacade();
    bool checkPassabilityOfSquare(int xCoord, int yCoord);
    bool checkPassabilityOfSquare(QPoint squarePoint);
    Personage *personageAt(QPoint point);
    void movePersonage(Personage *pers);
    QPoint toMapCoordinates(const QPointF &point)
    {
        return QPoint(xToMapCoordinates(point), yToMapCoordinates(point));
    }
    qreal xToMapCoordinates(const QPointF &point);
    qreal yToMapCoordinates(const QPointF &point);
    QPointF squareCenter(int x, int y);
    QPointF squareCenter(QPoint point);
    void addPersonage(Personage *pers, int xCoord, int yCoord);
    void drawPersWay(Personage *pers);
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

public slots:
    void oneMove(Personage *pers);

protected:
    int xSquareNumber;
    int ySquareNumber;
    int squareSize;
    int xWidth;
    int yHeight;
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
    QMap <int, QMap <int, AStarPoint*> > aStarCells;
    bool pointExists(QPoint point);
};


