#pragma once

#include <QGraphicsView>

class GraphicsScene
{
public:
    GraphicsScene(int yHeight, int xWidth, QWidget *parent = 0)
    {
        scene = new QGraphicsScene();
        view = new QGraphicsView(scene, parent);
        view->setFixedSize(xWidth, 500);
        scene->setItemIndexMethod(QGraphicsScene::BspTreeIndex);

        view->show();
        scene->setSceneRect(QRectF());
        view->setSceneRect(scene->sceneRect());

        view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    }
//protected:
    QGraphicsView *view;
    QGraphicsScene *scene;
};
