#pragma once

#include "pixmap_item.h"

class MapObject
{
public:
    MapObject(const QPixmap& pixmap, int vert, int horiz) : objectPixmapItem(new PixmapItem(pixmap, vert, horiz)) {}
    MapObject(const QPixmap& pixmap) : objectPixmapItem(new PixmapItem(pixmap)) {}
    MapObject(PixmapItem *pixItem) : objectPixmapItem(pixItem) {}
    MapObject(const MapObject& objectToCopy) : objectPixmapItem(new PixmapItem(*(objectToCopy.objectPixmapItem))) {}
    virtual ~MapObject()
    {
        delete objectPixmapItem;
    }

    void setDrawingPriority(qreal priority)
    {
        this->objectPixmapItem->setZValue(priority);
    }
    qreal getDrawingPriority() const
    {
        return this->objectPixmapItem->zValue();
    }
    PixmapItem *objectPixmapItem;
};




