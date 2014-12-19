#pragma once


#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QDebug>

class PixmapItem : public QGraphicsPixmapItem
{
public:
    PixmapItem(const QPixmap& pixmap, int vert, int horiz)
        : QGraphicsPixmapItem(pixmap), vertCorr(vert), horizCorr(horiz) {}
    PixmapItem(const QPixmap& pixmap)
        : QGraphicsPixmapItem(pixmap),
          vertCorr((pixmap.width() / (-2)) - (pixmap.width() % 2)),
          horizCorr((pixmap.height() / (-2)) - (pixmap.height() % 2)) {}
    PixmapItem(const PixmapItem& pixItem) : QGraphicsPixmapItem(pixItem.pixmap()), vertCorr(pixItem.vertCorr),
        horizCorr(pixItem.horizCorr){}
    ~PixmapItem()
    {
        qDebug() << "PixmapItem deleted";
    }

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
protected:
    int vertCorr;
    int horizCorr;
};






