#include "prop_map.h"

void PropMap::removeAll()
{
    for (int i = 0; i < table.size(); i++)
    {
        for (int j = 0; j < table[i].size(); j++)
            delete table[i][j];
    }
    qDebug() << "prop_destr";
}

PropObject *PropMap::objectAt(int x, int y) const
{
    if (x >= 0 && x < xMapWidth && y >= 0 && y < yMapHeight)
    {
        qDebug() << "objectAt square number " << x << " " << y;
        return table[x][y];
    }
    else qDebug() << "error: incorrect square number " << x << " " << y;
}
