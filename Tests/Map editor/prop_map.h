#pragma once

#include <QVector>
#include "prop_object.h"
#include "prop_factory.h"

//тут может быть шаблон
class PropMap
{
public:
//    PropMap(); //can do problems with ui?
    PropMap(int xSize, int ySize, QList<PropType> list) : factory(new PropFactory), xMapWidth(xSize), yMapHeight(ySize), table(QVector<QVector <PropObject*> > (xMapWidth))
    {
        if ((xSize * ySize) != list.size())
            qDebug() << "PropMap list size is not correct";
        else
        {
            int i = 0;
            for (int x = 0; x < table.size(); x++)
            {
                table[x] = QVector <PropObject*> (yMapHeight);
                for (int y = 0; y < table[x].size(); y++)
                {
                    table[x][y] = factory->clone(list[i++]);
                }
            }
        }
    }
    PropMap(int xSize, int ySize) : factory(new PropFactory), xMapWidth(xSize), yMapHeight(ySize), table(QVector<QVector <PropObject*> > (xMapWidth))
    {
        for (int i = 0; i < table.size(); i++)
        {
            table[i] = QVector <PropObject*> (yMapHeight);
            for (int j = 0; j < table[i].size(); j++)
            {
                table[i][j] = nullptr;
            }
        }
    }

    void addProp(PropType type, int xCoord, int yCoord)
    {
        if (xCoord >= 0 && xCoord <= xMapWidth && yCoord >= 0 && yCoord <= yMapHeight)
        {
            delete table[xCoord][yCoord];
            table[xCoord][yCoord] = factory->clone(type);
        }
    }

    void removeAll();

    PropObject *objectAt(int x, int y);

    PropObject *objectAt(const QPoint &point);

    PropFactory *getFactory() const
    {
        return this->factory;
    }

    void setFactoryType(PropType type)
    {
        this->factory->setType(type);
    }

protected:
    PropFactory *factory;
    int xMapWidth;
    int yMapHeight;
    QVector<QVector<PropObject*> > table;
};
