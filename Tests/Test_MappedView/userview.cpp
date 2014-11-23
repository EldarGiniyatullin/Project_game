#include "userview.h"
#include "ui_userview.h"
#include "scenemanager.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QDebug>

UserView::UserView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserView)
{
    ui->setupUi(this);
    scenka = new SceneManager(500, 500, 50, this);
    scenka->grScene->scene->setSceneRect(QRectF());
    scenka->grScene->view->setSceneRect(scenka->grScene->scene->sceneRect());
    this->setCentralWidget(scenka->grScene->view);
    scenka->grScene->view->show();
}

UserView::~UserView()
{
    delete ui;
}

void UserView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        qDebug() << "Cursor Pos = " << QCursor :: pos();
        qDebug() << "WidgetAt = " << QApplication::widgetAt(QCursor :: pos())->objectName();
        scenka->addItem(event->pos(), new MapObject(TreeObject()));
    }

    if (event->button() == Qt::RightButton)
    {
        qDebug() << QCursor :: pos();
        qDebug() << QApplication::widgetAt(QCursor :: pos())->objectName();
        scenka->addItem(event->pos(), new MapObject(GameObject()));
    }
}
