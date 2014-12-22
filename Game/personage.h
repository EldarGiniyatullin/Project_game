#pragma once

#include <QMap>
#include <QList>

#include "map_object.h"
#include "surface_object.h"

enum Fraction {GREEN = 0, BLACK, WHITE, ORANGE, RED, BLUE};
enum Speciality {WARRIOR = 0, WIZARD};


class Personage : public MapObject
{
public:

    Personage() :  MapObject(QPixmap("://No_image.png")), persFraction(RED), persSpeciality(WARRIOR), hp(1000), maxSteps(10), currentSteps(maxSteps) {}
	Personage(QPixmap pixmap, Fraction frac, Speciality spec, int xPos, int yPos)
        : MapObject(pixmap),  persFraction(frac), persSpeciality(spec), xCoord(xPos), yCoord(yPos), hp(1000), maxSteps(10), currentSteps(maxSteps) {wayToGo.clear();}

    Personage(QPixmap pixmap, int vertDraw, int horizDraw, Fraction frac, Speciality spec, int maximalSteps)
        :  MapObject(pixmap,  vertDraw, horizDraw), persFraction(frac), persSpeciality(spec), hp(1000), maxSteps(maximalSteps), currentSteps(maxSteps) {wayToGo.clear();}
    Personage(QPixmap pixmap, Fraction frac, Speciality spec, int maximalSteps) :  MapObject(pixmap), persFraction(frac), persSpeciality(spec), hp(1000), maxSteps(maximalSteps), currentSteps(maxSteps) {wayToGo.clear();}
    Personage(PixmapItem *pixItem, Fraction frac, Speciality spec) :  MapObject(pixItem), persFraction(frac), persSpeciality(spec),  hp(1000), maxSteps(10), currentSteps(maxSteps) {wayToGo.clear();}
    Personage(const Personage& personageToCopy) : hp(1000), MapObject(personageToCopy), persFraction(personageToCopy.persFraction),
        persSpeciality(personageToCopy.persSpeciality), maxSteps(personageToCopy.maxSteps), currentSteps(maxSteps) {}

	~Personage()
	{
		for (int i = 0; i < wayDrawing.size(); i++)
			delete wayDrawing[i];
	}

	void setPersPos(int xPos, int yPos);
	int getHP();
	void setHP(int hp);

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

    void updateSteps()
    {
        currentSteps = maxSteps;
    }

	Fraction getPersFraction() const
	{
		return persFraction;
	}
	void setPersFraction(const Fraction &value)
	{
		persFraction = value;
	}


	Personage &operator=(const Personage &pers);

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
            for (int i = 0; i < wayToGo.size() && i < currentSteps; i++)
			{
				wayDrawing.append(new PixmapItem(QPixmap("://dot.png")));
				wayDrawing.last()->setZValue(100);
			}
            int min = (wayToGo.size() < currentSteps ? wayToGo.size() : currentSteps);
            for (int i = min; i < wayToGo.size(); i++)
            {
                wayDrawing.append(new PixmapItem(QPixmap("://unpassable_dot.png")));
                wayDrawing.last()->setZValue(100);
            }
            if (wayDrawing.size())
                delete wayDrawing.takeLast();
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

    int getCurrentSteps() const;
    void setCurrentSteps(int value);

    int getMaxSteps() const;
    void setMaxSteps(int value);

protected:
    Fraction persFraction;
    Speciality persSpeciality;
    int xCoord;
	int yCoord;
	QList<QPoint> wayToGo;
	QList<PixmapItem*> wayDrawing;
	int hp;
    int maxSteps;
    int currentSteps;

};
