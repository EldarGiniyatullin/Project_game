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
    moveState(NOMOVE),
    QWidget(parent)
{
    listOfPersonages.clear();

    for (int i = 0; i < xSquareNumber; i++)
        for (int j = 0; j < ySquareNumber; j++)
        {
            if (surMap->objectAt(i, j))
            {
                mapScene->scene->addItem(surMap->objectAt(i, j)->objectPixmapItem);
                surMap->objectAt(i, j)->setPixPos(squareCenter(i, j), 0);
            }
            if (prMap->objectAt(i, j))
            {
                mapScene->scene->addItem(prMap->objectAt(i, j)->objectPixmapItem);
                prMap->objectAt(i, j)->setPixPos(squareCenter(i, j), j);
            }
        }
    this->resize(mapScene->view->size());
    mapScene->view->repaint();
}

MapFacade::MapFacade(const MapFacadeSaveObject &savedMap, int squareSide, QWidget *parent)
    : xSquareNumber(savedMap.xSquareNumber),
      ySquareNumber(savedMap.ySquareNumber),
      squareSize(squareSide),
      xWidth(savedMap.xSquareNumber * squareSide),
      yHeight(savedMap.ySquareNumber * squareSide),

      surMap(new SurfaceMap(xSquareNumber, ySquareNumber, savedMap.surfaces)),
      prMap(new PropMap(xSquareNumber, ySquareNumber, savedMap.props)),
      mapScene(new GraphicsScene(yHeight, xWidth, this)),
      persMaker(PersonageMaker(squareSide)),
      settedPers(nullptr),
      moveState(NOMOVE),
      QWidget(parent)
{


    for (int i = 0; i < xSquareNumber; i++)
        for (int j = 0; j < ySquareNumber; j++)
        {
            if (surMap->objectAt(i, j))
            {
                mapScene->scene->addItem(surMap->objectAt(i, j)->objectPixmapItem);
                surMap->objectAt(i, j)->setPixPos(squareCenter(i, j), 0);
            }
            if (prMap->objectAt(i, j))
            {
                mapScene->scene->addItem(prMap->objectAt(i, j)->objectPixmapItem);
                prMap->objectAt(i, j)->setPixPos(squareCenter(i, j), j);
            }
        }
    if (savedMap.numberOfPersonages != savedMap.personages.size())
        qDebug() << "personages list size is not correct";
    else
    {
        for (int i = 0; i < savedMap.personages.size(); i++)
        {
            int xCoord = savedMap.personages[i].xCoord;
            int yCoord = savedMap.personages[i].yCoord;
            listOfPersonages.append(persMaker.makePers(savedMap.personages[i].frac, savedMap.personages[i].spec));
            listOfPersonages.last()->setPersPos(xCoord, yCoord);
            mapScene->scene->addItem(listOfPersonages.last()->objectPixmapItem);
            listOfPersonages.last()->setPixPos(squareCenter(xCoord, yCoord), ySquareNumber + yCoord);
        }
    }
    this->resize(mapScene->view->size());
    mapScene->view->repaint();
}



MapFacade::~MapFacade()
{
    prMap->removeAll();
    delete prMap;
    surMap->removeAll();
    delete surMap;
    for (int i = 0; i < listOfPersonages.size(); i++)
        delete listOfPersonages[i];
    delete mapScene;
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

Personage *MapFacade::personageAt(QPoint point)
{
    for (int i = 0; i < listOfPersonages.size(); i++)
    {
        if (listOfPersonages[i]->currentPos() == point)
        {
            qDebug() << "personage is";
            return listOfPersonages[i];
        }
    }
    qDebug() << "personage is not";
    return nullptr;
}

Personage *MapFacade::personageUnderMouse(QMouseEvent *event)
{
    return personageAt(globalToMapCoordinates(event->pos()));
}

PropObject *MapFacade::propUnderMouse(QMouseEvent *event)
{
    return prMap->objectAt(globalToMapCoordinates(event->pos()));
}

void MapFacade::movePersonage(Personage *pers)
{
    //sound
    //while !endOfMoves
    while (!pers->getWayToGo().isEmpty())
    {
        moveState = MOVE;
        QThread::msleep(100);
        oneMove(pers);
        qDebug() << pers->objectPixmapItem->isVisible();
    }
    moveState = NOMOVE;
    //if other click - break;
    //sound stop
}

void MapFacade::deletePersonage(Personage *pers)
{
    listOfPersonages.removeOne(pers);
    delete pers;
}

qreal MapFacade::xToMapCoordinates(const QPointF &point)
{
    return (point.x() + (xWidth / 2)) / squareSize;
}

qreal MapFacade::yToMapCoordinates(const QPointF &point)
{
    return (point.y() + (yHeight / 2))  / squareSize;
}

QPointF MapFacade::squareCenter(QPoint point)
{
    return squareCenter(point.x(), point.y());
}


void MapFacade::addPersonage(Personage *pers, int xCoord, int yCoord)
{
    listOfPersonages.append(pers);
    pers->setPersPos(xCoord, yCoord);
    mapScene->scene->addItem(pers->objectPixmapItem);
    pers->setPixPos(squareCenter(xCoord, yCoord), yCoord + ySquareNumber);
}

void MapFacade::drawPersWay(Personage *pers)
{
    for (int i = 0; i < pers->getWayDrawning().size(); i++)
    {
        mapScene->scene->addItem(pers->getWayDrawning()[i]);
        pers->getWayDrawning()[i]->setPos(squareCenter(pers->getWayToGo()[i]));
    }
}

//void MapFacade::mousePressEvent(QMouseEvent *event)
//{

//    QPointF floatPoint = mapScene->view->mapToScene(event->pos());
//    if (event->button() == Qt::LeftButton)
//    {
//        qDebug() << "Checking passability " << floatPoint;
//        qDebug() << toMapCoordinates(floatPoint) << " " << checkPassabilityOfSquare(toMapCoordinates(floatPoint));
//        settedPers =  personageAt(toMapCoordinates(floatPoint));
//    }
//    if (event->button() == Qt::RightButton)
//    {
//        if (settedPers)
//        {
//            buildWay(settedPers, toMapCoordinates(floatPoint));
//            drawPersWay(settedPers);
//        }
//    }
//}

//void MapFacade::keyPressEvent(QKeyEvent *event)
//{
//    if (event->key() == Qt::Key_Space && settedPers)
//        this->movePersonage(settedPers);
//}

void MapFacade::addSurfaceFromMouse(QMouseEvent *event, SurfaceType type)
{
    QPoint point = globalToMapCoordinates(event->pos());
    this->surMap->addSurface(type, point.x(), point.y());
    this->mapScene->addItem(this->surMap->objectAt(point.x(), point.y())->objectPixmapItem);
    this->surMap->objectAt(point.x(), point.y())->setPixPos(this->squareCenter(point), 0);
    this->surMap->objectAt(point.x(), point.y())->setDrawingPriority(point.y());
}

void MapFacade::addSurfaceFromMouse(QMouseEvent *event)
{
    return addSurfaceFromMouse(event, surMap->getFactory()->currentType);

}

void MapFacade::addPropFromMouse(QMouseEvent *event, PropType type)
{
    QPoint point = globalToMapCoordinates(event->pos());
    this->prMap->addProp(type, point.x(), point.y());
    if (type != NULLOBJECT)
    {
        this->mapScene->addItem(this->prMap->objectAt(point.x(), point.y())->objectPixmapItem);
        this->prMap->objectAt(point.x(), point.y())->setPixPos(this->squareCenter(point), point.y());
    }
}

void MapFacade::addPropFromMouse(QMouseEvent *event)
{
    return addPropFromMouse(event, prMap->getFactory()->currentType);
}

void MapFacade::addPersonageFromMouse(QMouseEvent *event, Fraction frac, Speciality spec)
{
    Personage *pers = persMaker.makePers(frac, spec);
    QPoint point = globalToMapCoordinates(event->pos());
    pers->setPersPos(point.x(), point.y());
    this->addPersonage(pers, point.x(), point.y());
}

void MapFacade::oneMove(Personage *pers)
{
    if (!pers->getWayToGo().isEmpty())
    {
        QPoint point = pers->getWayToGo().first();
        //центр камеры на него
        if ((abs(pers->getXCoord() - point.x()) > 1) || (abs(pers->getYCoord() - point.y()) > 1))
        {
            delete pers->getWayDrawning().takeFirst();
            pers->setPersPos(point.x(), point.y());
            pers->setPixPos(squareCenter(point), ySquareNumber + point.y());
            pers->getWayToGo().takeFirst();
        }
        else
        {
            // можно добавить еще к анимации, поэтому выделено отдельно
            delete pers->getWayDrawning().takeFirst();
            pers->setPersPos(point.x(), point.y());
            pers->setPixPos(squareCenter(point), point.y() + ySquareNumber);
            pers->getWayToGo().takeFirst();
        }
        //better to "update" optimal rect in scene
        mapScene->view->repaint();
    }
}

void MapFacade::buildWay(Personage *pers, QPoint point)
{
    qDebug() << pers->currentPos();
    for (int i = 0; i < xSquareNumber; i++)
    {
        for (int j = 0; j < ySquareNumber; j++)
        {
            aStarCells[i][j] = new AStarPoint(QPoint(i, j), checkPassabilityOfSquare(i, j));
        }
    }

    if ((pers->currentPos() != point) && (checkPassabilityOfSquare(point)))
    {
        QList<QPoint*> path;

        AStarPoint *start = getPointFromCoord(pers->currentPos());
        AStarPoint *end = getPointFromCoord(point);
        AStarPoint *current;
        AStarPoint *child;

        QList<AStarPoint*> openList;
        QList<AStarPoint*> closedList;
        QList<AStarPoint*>::iterator i;

        unsigned int n = 0;

        openList.push_back(start);
        start->opened = true;

        while (n == 0 || (current != end && n < xSquareNumber * ySquareNumber))
        {
            for (i = openList.begin(); i != openList.end(); ++i)
            {
                if (i == openList.begin() || (*i)->getFScore() <= current->getFScore())
                {
                    current = (*i);
                }
            }

            if (current == end)
            {
                break;
            }

            openList.removeOne(current);
            current->opened = false;

            closedList.push_back(current);
            current->closed = true;

            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    if (x == 0 && y == 0)
                    {
                        continue;
                    }

                    child = getPoint(QPoint(current->getX() + x, current->getY() + y));

                    if (child->closed || !child->walkable)
                    {
                        continue;
                    }

                    if (x != 0 && y != 0)
                    {
                        if (!checkPassabilityOfSquare(QPoint(current->getX(), current->getY() + y)) || getPoint(QPoint(current->getX(), current->getY() + y))->closed)
                        {
                            continue;
                        }

                        if (!checkPassabilityOfSquare(QPoint(current->getX() + x, current->getY())) || getPoint(QPoint(current->getX() + x, current->getY()))->closed)
                        {
                            continue;
                        }
                    }

                    if (child->opened)
                    {
                        if (child->getGScore() > child->getGScore(current))
                        {
                            child->setParent(current);
                            child->computeScores(end);
                        }
                    }
                    else
                    {
                        openList.push_back(child);
                        child->opened = true;

                        child->setParent(current);
                        child->computeScores(end);
                    }
                }
            }

            n ++;
        }

        for (i = openList.begin(); i != openList.end(); ++i)
        {
            (*i)->opened = false;
        }
        for (i = closedList.begin(); i != closedList.end(); ++i)
        {
            (*i)->closed = false;
        }

        while (current->hasParent() && current != start)
        {
            path.push_back(current->getPosition());
            current = current->getParent();
            n++;
        }

        if (!path.empty() && (QPoint(path.first()->x(), path.first()->y()) == point))
        {
            pers->clearWayToGo();
            QList<QPoint *>::iterator i;

            for (i = path.begin(); i != path.end(); ++i)
            {
                pers->getWayToGo().prepend(QPoint((*i)->x(), (*i)->y()));
                qDebug() <<  '\n' << (*i)->x() << (*i)->y() << '\n';
            }

            pers->buildWayDrawning();
            this->drawPersWay(pers);
        }
    }

    for (int i = 0; i < xSquareNumber; i++)
    {
        for (int j = 0; j < ySquareNumber; j++)
        {
            delete aStarCells[i][j];
        }
    }
}

AStarPoint *MapFacade::getPoint(QPoint point)
{
    if (pointExists(point))
    {
        return aStarCells[point.x()][point.y()];
    }
    else
    {
        return new AStarPoint(QPoint(0, 0), false);
    }
}

bool MapFacade::pointExists(QPoint point)
{
    return (point.x() >= 0 && point.y() >=0 && point.x() < xSquareNumber && point.y() < ySquareNumber);
}

AStarPoint *MapFacade::getPointFromCoord(QPoint coord)
{
    return getPoint(coord);
}

QPointF MapFacade::squareCenter(int x, int y)
{
    return QPointF(squareSize * x + (squareSize / 2) + 1 - (xWidth / 2), squareSize * y +(squareSize / 2) + 1 - (yHeight / 2));
}
