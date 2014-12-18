#include "graphics_scene.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QRect>


GraphicsScene::GraphicsScene(int yHeight, int xWidth, QWidget *parent)
{
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene, parent);
    QRect screenRect = QApplication::desktop()->screenGeometry();
    view->setFixedSize((screenRect.width() - 300 < xWidth ? screenRect.width() - 300 : xWidth), (screenRect.height() - 100 < yHeight ? screenRect.height() - 100 : yHeight));
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    scene->setItemIndexMethod(QGraphicsScene::BspTreeIndex);

    view->show();
    scene->setSceneRect(QRectF());
    view->setSceneRect(xWidth / (-2), yHeight / (-2), xWidth, yHeight);


    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

}
