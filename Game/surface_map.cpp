#include "surface_map.h"


void SurfaceMap::removeAll()
{
    for (int i = 0; i < table.size(); i++)
    {
        for (int j = 0; j < table[i].size(); j++)
            delete table[i][j];
    }
    qDebug() << "surf_destr";
}
