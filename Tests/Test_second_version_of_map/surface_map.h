#pragma once

#include <QVector>
#include "surface_object.h"

//тут может быть шаблон
class SurfaceMap
{
public:
//    SurfaceMap(); //can do problems with ui?
    SurfaceMap(int xSize, int ySize) : factory(new SurfaceFactory), xMapWidth(xSize), yMapHeight(ySize), table(QVector<QVector <SurfaceObject*> > (xMapWidth))
    {
        for (int i = 0; i < table.size(); i++)
        {
            table[i] = QVector <SurfaceObject*> (yMapHeight);
            for (int j = 0; j < table[i].size(); j++)
            {
                if (i % 5 == 0 && j % 5 == 0)
                    table[i][j] = factory->clone(ROAD);
                else if (i % 19 == 0 && j % 19 == 0)
                    table[i][j] = factory->clone(ROCKS);
                else if (i % 13 == 0 && j % 13 == 0)
                    table[i][j] = factory->clone(WATER);
                else if (i % 31 == 0 && j % 31 == 0)
                    table[i][j] = factory->clone(SWAMP);
                else table[i][j] = factory->clone(FIELD);
            }
        }
    }
    SurfaceObject* objectAt(int x, int y) const
    {
        if (x >=0 && x < xMapWidth && y >= 0 && y < yMapHeight)
        {
            if (table[x][y])
            {
                qDebug() << "surf objectAt square number " << x << " " << y;
                return table[x][y];
            }
            else qDebug() << "surf error: nullptr square number " << x << " " << y;
        }
        else qDebug() << "surf error: incorrect square number " << x << " " << y;
    }

protected:
    SurfaceFactory *factory;
    int xMapWidth;
    int yMapHeight;
    QVector<QVector<SurfaceObject*> > table;
};
