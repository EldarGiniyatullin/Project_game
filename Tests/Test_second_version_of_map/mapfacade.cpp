#include "mapfacade.h"
#include "ui_mapfacade.h"

MapFacade::MapFacade(int xSquareNum, int ySquareNum, int squareSide, QWidget *parent) :
    xSquareNumber(xSquareNum),
    ySquareNumber(ySquareNum),
    squareSize(squareSide),
    xWidth(xSquareNum * squareSide),
    yHeight(ySquareNum * squareSide),
    //    personageMap(ObjectMap(xSquareNumber, ySquareNumber)<Personage>),

    surMap(new SurfaceMap(xSquareNum, ySquareNum)),
    prMap(new PropMap(xSquareNum, ySquareNum)),
    mapScene(new GraphicsScene(yHeight, xWidth, this)),
    QWidget(parent),
    ui(new Ui::MapFacade)
{
    ui->setupUi(this);




    for (int i = 0; i < xSquareNumber; i++)
        for (int j = 0; j < ySquareNumber; j++)
        {
            if (surMap->objectAt(i, j))
            {
                mapScene->scene->addItem(surMap->objectAt(i, j)->objectPixmapItem);
                surMap->objectAt(i, j)->objectPixmapItem->PixmapItem::setPos(squareCenter(i, j));
            }
            if (prMap->objectAt(i, j))
            {
                mapScene->scene->addItem(prMap->objectAt(i, j)->objectPixmapItem);
                prMap->objectAt(i, j)->objectPixmapItem->PixmapItem::setPos(squareCenter(i, j));
            }
        }
}

MapFacade::~MapFacade()
{
    delete ui;
}

bool MapFacade::checkPassabilityOfSquare(int xCoord, int yCoord)
{
    qDebug() << xCoord << " " << yCoord <<  " " << "Passability = " << (surMap->objectAt(xCoord, yCoord)->getIsPassable() && (prMap->objectAt(xCoord, yCoord) ? prMap->objectAt(xCoord, yCoord)->getIsPassable() : true));
    //----------------------------------------------------------------------------------------------------------------------------------
    return (surMap->objectAt(xCoord, yCoord)->getIsPassable() && (prMap->objectAt(xCoord, yCoord) ? prMap->objectAt(xCoord, yCoord)->getIsPassable() : true));
    //----------------------------------------------------------------------------------------------------------------------------------
}

bool MapFacade::checkPassabilityOfSquare(QPoint squarePoint)
{
    return checkPassabilityOfSquare(squarePoint.x(), squarePoint.y());
}

void MapFacade::addPersonage(Personage *pers)
{
    connect(dynamic_cast<QObject*>(pers), SIGNAL(Personage::moveMeToPosition(QPoint point)), this, SLOT(buildWay(Perdonage* pers, point)));
}

void MapFacade::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPointF floatPoint = mapScene->view->mapToScene(event->pos());
        qDebug() << "Checking passability " << floatPoint;
        qDebug() << toMapCoordinates(floatPoint) << " " << checkPassabilityOfSquare(toMapCoordinates(floatPoint));
    }
}

void MapFacade::buildWay(Personage *pers, QPoint point)
{

}
