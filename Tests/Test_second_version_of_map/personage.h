#pragma once

#include <QList>
#include <QObject>

#include "map_object.h"
#include "surface_object.h"

enum Fraction {GREEN = 0, BLACK, WHITE, ORANGE, RED};


class Personage : public QObject,  public MapObject
{
    Q_OBJECT
public:

    Personage() : QObject(), MapObject(QPixmap("://No_image.png")), persFraction(GREEN) {}
    Personage(QPixmap pixmap, Fraction frac, int xPos, int yPos)
        : QObject(), MapObject(pixmap),  persFraction(frac), xCoord(xPos), yCoord(yPos) {wayToGo.clear();}

    Personage(QPixmap pixmap, Fraction frac, int xPos, int yPos, int vertDraw, int horizDraw)
        : QObject(), MapObject(pixmap, vertDraw, horizDraw), persFraction(frac), xCoord(xPos), yCoord(yPos) {wayToGo.clear();}
    Personage(QPixmap pixmap, Fraction frac) : QObject(), MapObject(pixmap), persFraction(frac) {wayToGo.clear();}
    Personage(PixmapItem *pixItem, Fraction frac) : QObject(), MapObject(pixItem), persFraction(frac) {wayToGo.clear();}
//    Personage(const Personage& personageToCopy) : MapObject(personageToCopy), type(objectToCopy.getSurfaceType()) {}
//    ~Personage();
    void setPos(int xPos, int yPos)
    {
        xCoord = xPos;
        yCoord = yPos;
    }

    void moveTo(int xSquare, int ySquare)
    {
        emit moveMeToPosition(QPoint(xSquare, ySquare));
    }
    QList<QPoint> personageWay()
    {
        return wayToGo;
    }


signals:
    void moveMeToPosition(QPoint point);

protected:
    Fraction persFraction;
    int xCoord;
    int yCoord;
    QList<QPoint> wayToGo;

};



