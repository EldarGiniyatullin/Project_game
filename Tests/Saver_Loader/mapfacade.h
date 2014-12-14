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
#include "mapfacade_save_object.h"


namespace Ui {
class MapFacade;
}

enum PersonageMoveState {NOMOVE, MOVE};

class MapFacade : public QWidget
{
    Q_OBJECT

public:
    MapFacade(int xSquareNum, int ySquareNum, int squareSide, QWidget *parent = 0);
    MapFacade(const MapFacadeSaveObject& savedMap, int squareSide, QWidget *parent = 0);
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

    MapFacadeSaveObject saveToObject()
    {
        MapFacadeSaveObject  saveObject;
        saveObject.numberOfPersonages = listOfPersonages.size();
        saveObject.xSquareNumber = this->xSquareNumber;
        saveObject.ySquareNumber = this->ySquareNumber;
        saveObject.props.clear();
        for (int x = 0; x < xSquareNumber; x++)
            for (int y = 0; y < ySquareNumber; y++)
            {
                saveObject.props.append(prMap->objectAt(x, y)->getPropType());
                saveObject.surfaces.append(surMap->objectAt(x, y)->getSurfaceType());
            }
        for (int i = 0; i < saveObject.numberOfPersonages; i++)
            saveObject.personages.append(MapFacadeSaveObject::SavedPersonage(listOfPersonages[i]->getPersFraction(), listOfPersonages[i]->getPersSpeciality()));
    }

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
    PersonageMoveState moveState;

public slots:
    void buildWay(Personage* pers, QPoint point);

private:
    Ui::MapFacade *ui;
    AStarPoint *getPoint(QPoint point);
    AStarPoint *getPointFromCoord(QPoint coord);
    QMap <int, QMap <int, AStarPoint*> > aStarCells;
    bool pointExists(QPoint point);
};


