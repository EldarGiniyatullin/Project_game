#pragma once


#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QDebug>

class PixmapItem : public QGraphicsPixmapItem
{
public:
    PixmapItem(QPixmap pixmap, int vert, int horiz)
        : QGraphicsPixmapItem(pixmap), vertCorr(vert), horizCorr(horiz) {}
    PixmapItem(QPixmap pixmap)
        : QGraphicsPixmapItem(pixmap),
          vertCorr((pixmap.width() / (-2)) - (pixmap.width() % 2)),
          horizCorr((pixmap.height() / (-2)) - (pixmap.height() % 2)) {}
    PixmapItem(const PixmapItem& pixItem) : QGraphicsPixmapItem(pixItem.pixmap()), vertCorr(pixItem.vertCorr),
        horizCorr(pixItem.horizCorr){}
    int vertCorr;
    int horizCorr;
    void setCorr(int x, int y)
    {
        vertCorr = x;
        horizCorr = y;
    }

    void setPos(qreal x, qreal y)
    {
        QGraphicsPixmapItem::setPos(x + vertCorr, y + horizCorr);
        qDebug() << x + vertCorr << " " << y + horizCorr;
    }
    void setPos(const QPointF &pos)
    {
        this->PixmapItem::setPos(pos.x(), pos.y());
    }
};

class MapObject
{
public:
    MapObject(QPixmap pixmap, int vert, int horiz) : objectPixmapItem(new PixmapItem(pixmap, vert, horiz)) {}
    MapObject(QPixmap pixmap) : objectPixmapItem(new PixmapItem(pixmap)) {}
    MapObject(PixmapItem *pixItem) : objectPixmapItem(pixItem) {}
    MapObject(const MapObject& objectToCopy) : objectPixmapItem(new PixmapItem(*(objectToCopy.objectPixmapItem))) {}
    ~MapObject()
    {
        delete objectPixmapItem;
    }

    void setDrawingPriority(int priority)
    {
        this->objectPixmapItem->setZValue(priority);
    }
    PixmapItem *objectPixmapItem;
};










