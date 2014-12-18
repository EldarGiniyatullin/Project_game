#pragma once

#include <QVector>

template <typename T>
class ObjectMap
{
public:
    ObjectMap(int xSize, int ySize) : xMapWidth(xSize), yMapHeight(ySize), table(QVector<QVector <T*> > (yMapHeight))
    {
        for (int i = 0; i < table.size(); i++)
        {
            table[i] = QVector <T*> (xMapWidth);
            for (int j = 0; j < table[i].size(); j++)
            {
 //------------- proplems with copying!!!--------------------------------------------------
                table[i][j] = nullptr;
            }
        }
    }
    const T& objectAt(int x, int y)
    {
        qDebug() << "passability at square number " << x << y;
        if (x >=0 && x <= xMapWidth && y >= 0 && y <= yMapHeight)
        return table[x][y];
    }

protected:
    QVector<QVector<T*> > table;
    int xMapWidth;
    int yMapHeight;
};
