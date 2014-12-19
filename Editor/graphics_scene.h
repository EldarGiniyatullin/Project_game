#pragma once

#include <QGraphicsView>

class GraphicsScene
{
public:
    GraphicsScene(int yHeight, int xWidth, QWidget *parent = 0);
    ~GraphicsScene()
    {
        delete view;
        delete scene;
    }

    void addItem(QGraphicsItem *item)
    {
        this->scene->addItem(item);
    }

//protected:
    QGraphicsView *view;
    QGraphicsScene *scene;
};
