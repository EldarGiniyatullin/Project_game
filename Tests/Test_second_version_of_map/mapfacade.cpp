#include "mapfacade.h"
#include "ui_mapfacade.h"

MapFacade::MapFacade(int xSquareNum, int ySquareNum, int squareSide, QWidget *parent) :
    xSquareNumber(xSquareNum),
    ySquareNumber(ySquareNum),
    squareSize(squareSide),
    xWidth(xSquareNum * squareSide),
    yHeight(ySquareNum * squareSide),

    surMap(new SurfaceMap(xSquareNum, ySquareNum)),
    prMap(new PropMap(xSquareNum, ySquareNum)),
    mapScene(new GraphicsScene(yHeight, xWidth, this)),
    persMaker(PersonageMaker(squareSide)),
    settedPers(nullptr),
    QWidget(parent),
    ui(new Ui::MapFacade)
{
    ui->setupUi(this);
    listOfPersonages.clear();

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
    addPersonage(persMaker.makePers(GREEN, WARRIOR), 8, 8);
    this->resize(mapScene->view->size());
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

void MapFacade::addPersonage(Personage *pers, int xCoord, int yCoord)
{
    listOfPersonages.append(pers);
    connect(dynamic_cast<QObject*>(pers), SIGNAL(Personage::moveMeToPosition(QPoint point)), this, SLOT(buildWay(Personage* pers, point)));
    pers->setPos(xCoord, yCoord);
    mapScene->scene->addItem(pers->objectPixmapItem);
    pers->objectPixmapItem->setPos(squareCenter(xCoord, yCoord));
}

void MapFacade::drawPersWay(Personage *pers)
{
    for (int i = 0; i < pers->getWayDrawning().size(); i++)
    {
        mapScene->scene->addItem(pers->getWayDrawning()[i]);
        pers->getWayDrawning()[i]->setPos(squareCenter(pers->getWayToGo()[i]));
    }
}

void MapFacade::mousePressEvent(QMouseEvent *event)
{

    QPointF floatPoint = mapScene->view->mapToScene(event->pos());
    if (event->button() == Qt::LeftButton)
    {
        qDebug() << "Checking passability " << floatPoint;
        qDebug() << toMapCoordinates(floatPoint) << " " << checkPassabilityOfSquare(toMapCoordinates(floatPoint));
        settedPers =  personageAt(toMapCoordinates(floatPoint));
    }
    if (event->button() == Qt::RightButton)
    {
        if (settedPers)
        {
            buildWay(settedPers, toMapCoordinates(floatPoint));
            drawPersWay(settedPers);
        }
    }
}

void MapFacade::buildWay(Personage *pers, QPoint point)
{
    qDebug() << pers->currentPos();
    if ((pers->currentPos() != point) && (checkPassabilityOfSquare(point)))
    {
        pers->clearWayToGo();
        QPoint tempPoint = pers->currentPos();
        bool isPass = true;
        //---------------
        int inci = (point.x() <= pers->currentPos().x() ? -1 : 1);
        int incj = (point.y() <= pers->currentPos().y() ? -1 : 1);
        while (tempPoint.x() != point.x() && isPass)
        {
            tempPoint.setX(tempPoint.x() + inci);
            if (checkPassabilityOfSquare(tempPoint))
                pers->getWayToGo().append(QPoint(tempPoint.x(), tempPoint.y()));
            else
                isPass = false;
        }
        if (isPass)
        {
            while (tempPoint.y() != point.y() && isPass)
            {
                tempPoint.setY(tempPoint.y() + incj);
                if (checkPassabilityOfSquare(tempPoint))
                    pers->getWayToGo().append(QPoint(tempPoint.x(), tempPoint.y()));
                else
                    isPass = false;
            }
        }
        if (isPass)
        {
            pers->buildWayDrawning();
            this->drawPersWay(pers);
        }
        else pers->clearWayToGo();
        //---------------
    }
}
