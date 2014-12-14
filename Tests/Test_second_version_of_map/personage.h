#pragma once

#include <QMap>
#include <QList>
#include <QObject>

#include "map_object.h"
#include "surface_object.h"

enum Fraction {GREEN = 0, BLACK, WHITE, ORANGE, RED};
enum Speciality {WARRIOR = 0, WIZARD};


class Personage : public QObject,  public MapObject
{
    Q_OBJECT
public:

    Personage() : QObject(), MapObject(QPixmap("://No_image.png")), persFraction(GREEN), persSpeciality(WARRIOR) {}
    Personage(QPixmap pixmap, Fraction frac, Speciality spec, int xPos, int yPos)
        : QObject(), MapObject(pixmap),  persFraction(frac), persSpeciality(spec), xCoord(xPos), yCoord(yPos) {wayToGo.clear();}

    Personage(QPixmap pixmap, int vertDraw, int horizDraw, Fraction frac, Speciality spec)
        : QObject(), MapObject(pixmap, vertDraw, horizDraw), persFraction(frac), persSpeciality(spec) {wayToGo.clear();}
    Personage(QPixmap pixmap, Fraction frac, Speciality spec) : QObject(), MapObject(pixmap), persFraction(frac), persSpeciality(spec) {wayToGo.clear();}
    Personage(PixmapItem *pixItem, Fraction frac, Speciality spec) : QObject(), MapObject(pixItem), persFraction(frac), persSpeciality(spec) {wayToGo.clear();}
    Personage(const Personage& personageToCopy) : QObject(), MapObject(personageToCopy), persFraction(personageToCopy.persFraction),
        persSpeciality(personageToCopy.persSpeciality) {}
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
    QPoint currentPos()
    {
        return QPoint(xCoord, yCoord);
    }

    Speciality getPersSpeciality() const
    {
        return persSpeciality;
    }
    void setPersSpeciality(const Speciality &value)
    {
        persSpeciality = value;
    }

    Fraction getPersFraction() const
    {
        return persFraction;
    }
    void setPersFraction(const Fraction &value)
    {
        persFraction = value;
    }


   Personage &operator=(const Personage &pers)
   {
       Personage temp(pers);
       return temp;
   }

   QList<QPoint> &getWayToGo()
   {
       return wayToGo;
   }
   void clearWayToGo()
   {
       wayToGo.clear();
       while (!wayDrawing.isEmpty())
       {
           delete wayDrawing.takeFirst();
       }
   }

   QList<PixmapItem*> &getWayDrawning()
   {
       return wayDrawing;
   }
   void clearWayDrawning()
   {
       wayDrawing.clear();
   }
   void buildWayDrawning()
   {
       if (!wayToGo.isEmpty())
       {
           for (int i = 0; i < wayToGo.size() - 1; i++)
           {
                wayDrawing.append(new PixmapItem(QPixmap("://dot.png")));
                wayDrawing.last()->setZValue(100);
           }
           wayDrawing.append(new PixmapItem(QPixmap("://cross.png")));
           wayDrawing.last()->setZValue(100);
       }
   }

   int getXCoord() const
   {
       return xCoord;
   }
   void setXCoord(int value)
   {
       xCoord = value;
   }

   int getYCoord() const
   {
       return yCoord;
   }
   void setYCoord(int value)
   {
       yCoord = value;
   }

signals:
   void moveMeToPosition(QPoint point);

protected:
   Fraction persFraction;
    Speciality persSpeciality;
    int xCoord;
    int yCoord;
    QList<QPoint> wayToGo;
    QList<PixmapItem*> wayDrawing;

};

//it needs better realization
class PersonageMaker
{
public:
    PersonageMaker(int squareSize)
    {
        map.clear();
        QPixmap warrior("://first_personage.png");
        map.insert(WARRIOR, Personage(warrior, warrior.width() / (-2), (squareSize / 2) - warrior.height(), GREEN, WARRIOR));
    }

    Personage* makePers(Fraction frac, Speciality spec)
    {
        Personage *newPers(new Personage(map.value(spec)));
        newPers->setPersFraction(frac);
        return newPers;
    }
protected:
    QMap<Speciality, Personage> map;
};


















