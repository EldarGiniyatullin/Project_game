#include "mapfacade.h"
#include "ui_mapfacade.h"

MapFacade::MapFacade(int xSquareNum, int ySquareNum, int squareSide, QWidget *parent) :
         xSquareNumber(xSquareNum),
        ySquareNumber(ySquareNum),
        squareSize(squareSide),
        xWidth(xSquareNum * squareSide),
        yHeight(ySquareNum * squareSide),
    //    personageMap(ObjectMap(xSquareNumber, ySquareNumber)<Personage>),
    //    propsMap(ObjectMap(xSquareNumber, ySquareNumber)<PropObject>),
        surMap(new SurfaceMap(xSquareNum, ySquareNum)),
        mapScene(new GraphicsScene(yHeight, xWidth, this)),
    QWidget(parent),
    ui(new Ui::MapFacade)
{
    ui->setupUi(this);




    for (int i = 0; i < xSquareNumber; i++)
        for (int j = 0; j < ySquareNumber; j++)
        {
            mapScene->scene->addItem(surMap->objectAt(i, j).objectPixmapItem);
            surMap->objectAt(i, j).objectPixmapItem->PixmapItem::setPos(squareCenter(i, j));
        }
}

MapFacade::~MapFacade()
{
    delete ui;
}

bool MapFacade::checkPassabilityOfSquare(int xCoord, int yCoord)
{
    qDebug() << xCoord << " " << yCoord <<  " " << "Passability = " << surMap->objectAt(xCoord, yCoord).getIsPassable();
    return surMap->objectAt(xCoord, yCoord).getIsPassable();
}
