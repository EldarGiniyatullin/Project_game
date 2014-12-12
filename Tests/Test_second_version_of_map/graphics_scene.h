#pragma once

#include <QGraphicsView>

class GraphicsScene
{
public:
    GraphicsScene(int yHeight, int xWidth, QWidget *parent = 0)
    {
        scene = new QGraphicsScene();
        view = new QGraphicsView(scene, parent);
        view->setFixedSize(xWidth, 1000);
        view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
        scene->setItemIndexMethod(QGraphicsScene::BspTreeIndex);

        view->show();
        scene->setSceneRect(QRectF());
        view->setSceneRect(xWidth / (-2), yHeight / (-2), xWidth, yHeight);


        view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    }
//protected:
    QGraphicsView *view;
    QGraphicsScene *scene;
};
