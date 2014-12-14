#pragma once

#include <QList>
#include <QVector>
#include <QDebug>
#include "prop_object.h"
#include "prop_factory.h"

//тут может быть шаблон
class PropMap
{
public:
//    PropMap(); //can do problems with ui?
    PropMap(int xSize, int ySize, QList<PropType> list) : factory(new PropFactory), xMapWidth(xSize), yMapHeight(ySize), table(QVector<QVector <PropObject*> > (xMapWidth))
    {
        if ((xSize * ySize - 1) != list.size())
            qDebug() << "PropMap list size is not correct";
        else
        {
            QList<PropType>::Iterator iter = list.begin();
            for (int x = 0; x < table.size(); x++)
            {
                int i = 0;
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
            {                                                                 //раскомментируйте это, чтобы проверить выбегание из квадрата
                if (((i >= 0 && i <= 20 && (j == 0 || j == 20)) || (j >= 0 && j <= 20 && (i == 0 || i == 20)))/* && !(j == 7 && i == 20)*/)
                    table[i][j] = factory->clone(TREE_1);
                else table[i][j] == nullptr;
            }
        }
    }

    void removeAll();

    PropObject *objectAt(int x, int y) const;

protected:
    PropFactory *factory;
    int xMapWidth;
    int yMapHeight;
    QVector<QVector<PropObject*> > table;
};
