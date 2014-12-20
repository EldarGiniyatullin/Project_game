#pragma once

#include <QThread>
#include <QKeyEvent>
#include <cmath>
#include <QTimer>
#include <QWidget>
#include <QDebug>
#include <QMouseEvent>
#include <QList>

#include "graphics_scene.h"
#include "surface_map.h"
#include "prop_map.h"
#include "personage.h"
#include "astarpoint.h"
#include "personage_maker.h"


enum PersonageMoveState {NOMOVE, MOVE};

class MapFacadeSaveObject
{
public:
    MapFacadeSaveObject()
    {

    }

    int xSquareNumber;
    int ySquareNumber;
    int numberOfPersonages;
    QString saveName;
    struct SavedPersonage
    {
        SavedPersonage(Fraction fraction, Speciality speciality, int x, int y)
        {
            frac = fraction;
            spec = speciality;
            xCoord = x;
            yCoord = y;
        }

        Fraction frac;
        Speciality spec;
        int xCoord;
        int yCoord;
    };
    QList <SavedPersonage> personages;
    QList <PropType> props;
    QList <SurfaceType> surfaces;
};



class MapFacade : public QWidget
{
    Q_OBJECT

public:
    MapFacade(int xSquareNum, int ySquareNum, int squareSide, QWidget *parent = 0);
    MapFacade(const MapFacadeSaveObject &savedMap, int squareSide, QWidget *parent);
    ~MapFacade();
    bool checkPassabilityOfSquare(int xCoord, int yCoord);
    bool checkPassabilityOfSquare(QPoint squarePoint);
    Personage *personageAt(QPoint point);
    Personage *personageUnderMouse(QMouseEvent *event);
    PropObject *propUnderMouse(QMouseEvent *event);
    void movePersonage(Personage *pers);
    void deletePersonage(Personage *pers);
    QPoint toMapCoordinates(const QPointF &point)
    {
        return QPoint(xToMapCoordinates(point), yToMapCoordinates(point));
    }
    qreal xToMapCoordinates(const QPointF &point);
    qreal yToMapCoordinates(const QPointF &point);
    QPointF squareCenter(int x, int y);
    QPointF squareCenter(QPoint point);
    void addPersonage(Personage *pers, int xCoord, int yCoord);
    bool checkPersWay(Personage *pers);
    void drawPersWay(Personage *pers);
    void hidePersWay(Personage *pers);
//    void mousePressEvent(QMouseEvent *event);
//    void keyPressEvent(QKeyEvent *event);
    QPoint globalToMapCoordinates(const QPoint& point)
    {
        return toMapCoordinates(mapScene->view->mapToScene(point));
    }

    void addSurfaceFromMouse(QMouseEvent *event, SurfaceType type);
    void addSurfaceFromMouse(QMouseEvent *event);
    void addPropFromMouse(QMouseEvent *event, PropType type);
    void addPropFromMouse(QMouseEvent *event);
    void addPersonageFromMouse(QMouseEvent *event, Fraction frac, Speciality spec);

    void setSurfaceFactoryType(SurfaceType type)
    {
        this->surMap->setFactoryType(type);
    }

    void setPropFactoryType(PropType type)
    {
        this->prMap->setFactoryType(type);
    }

    void addPropObject(PropType type, int xCoord, int yCoord)
    {
        prMap->addProp(type, xCoord, yCoord);
    }

    QGraphicsView *getView()
    {
        return mapScene->view;
    }

    MapFacadeSaveObject saveToObject()
    {
        MapFacadeSaveObject saveObject;
        saveObject.numberOfPersonages = listOfPersonages.size();
        saveObject.xSquareNumber = this->xSquareNumber;
        saveObject.ySquareNumber = this->ySquareNumber;
        for (int x = 0; x < xSquareNumber; x++)
            for (int y = 0; y < ySquareNumber; y++)
            {
                if (prMap->objectAt(x, y))
                {
                    PropType type = prMap->objectAt(x, y)->getPropType();
                    saveObject.props.append(type);
                }
                else
                    saveObject.props.append(NULLOBJECT);
                saveObject.surfaces.append(surMap->objectAt(x, y)->getSurfaceType());
            }
        for (int i = 0; i < saveObject.numberOfPersonages; i++)
        {
            Personage *currPers = listOfPersonages[i];
            saveObject.personages.append(MapFacadeSaveObject::SavedPersonage(currPers->getPersFraction(), currPers->getPersSpeciality(), currPers->getXCoord(), currPers->getYCoord()));
        }
        return saveObject;
    }

    friend class GameWidget;

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
    AStarPoint *getPoint(QPoint point);
    AStarPoint *getPointFromCoord(QPoint coord);
    QMap <int, QMap <int, AStarPoint*> > aStarCells;
    bool pointExists(QPoint point);
};


