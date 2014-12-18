#pragma once

#include <QVector>
#include "surface_object.h"
#include "surface_factory.h"

//тут может быть шаблон
class SurfaceMap
{
public:
//    SurfaceMap(); //can do problems with ui?
    SurfaceMap(int xSize, int ySize, QList<SurfaceType> list) : factory(new SurfaceFactory), xMapWidth(xSize), yMapHeight(ySize), table(QVector<QVector <SurfaceObject*> > (xMapWidth))
    {
        if ((xSize * ySize) != list.size())
            qDebug() << "SurfaceMap list size is not correct";
        else
        {
            int i = 0;
            for (int x = 0; x < table.size(); x++)
            {
                table[x] = QVector <SurfaceObject*> (yMapHeight);
                for (int y = 0; y < table[x].size(); y++)
                {
                    table[x][y] = factory->clone(list[i++]);
                }
            }
        }
    }


    SurfaceMap(int xSize, int ySize) : factory(new SurfaceFactory), xMapWidth(xSize), yMapHeight(ySize), table(QVector<QVector <SurfaceObject*> > (xMapWidth))
    {
        for (int i = 0; i < table.size(); i++)
        {
            table[i] = QVector <SurfaceObject*> (yMapHeight);
            for (int j = 0; j < table[i].size(); j++)
            {
                table[i][j] = factory->clone(FIELD);
            }
        }
    }

    void removeAll();

    SurfaceObject* objectAt(int x, int y)
    {
        if (x >=0 && x < xMapWidth && y >= 0 && y < yMapHeight)
        {
            if (table[x][y])
            {
//                qDebug() << "surf objectAt square number " << x << " " << y;
                return table[x][y];
            }
            else qDebug() << "surf error: nullptr square number " << x << " " << y;
        }
        else qDebug() << "surf error: incorrect square number " << x << " " << y;
    }

    void addSurface(SurfaceType type, int xCoord, int yCoord)
    {
        if (xCoord >= 0 && xCoord <= xMapWidth && yCoord >= 0 && yCoord <= yMapHeight)
        {
            delete table[xCoord][yCoord];
            table[xCoord][yCoord] = factory->clone(type);
        }
    }

    void addSurface(SurfaceObject *object, int xCoord, int yCoord)
    {
        if (xCoord >= 0 && xCoord <= xMapWidth && yCoord >= 0 && yCoord <= yMapHeight)
        {
            delete table[xCoord][yCoord];
            table[xCoord][yCoord] = object;
        }
    }

    SurfaceFactory *getFactory() const
    {
        return this->factory;
    }

    void setFactoryType(SurfaceType type)
    {
        this->factory->setType(type);
    }

protected:
    SurfaceFactory *factory;
    int xMapWidth;
    int yMapHeight;
    QVector<QVector<SurfaceObject*> > table;
};



