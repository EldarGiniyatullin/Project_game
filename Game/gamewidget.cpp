#include "gamewidget.h"

GameWidget::GameWidget(QWidget *parent) :
    currentFractionsMove(RED),
    settedPersonage(nullptr),
    redPlayer(PLAYER),
    bluePlayer(COMPUTER),
    currentPlayer(redPlayer),
    QWidget(parent)
{
    editorLayout = new QHBoxLayout(this);
    gameMap = nullptr;
    //    editorLayout->addWidget(editMap->getView());
    buttonsLayout = new QGridLayout(this);

        QWidget *palitre = new QWidget;
        palitre->setLayout(buttonsLayout);
        palitre->setFixedHeight(300);
        palitre->setFixedWidth(250);
        editorLayout->addWidget(palitre, 0, Qt::AlignRight | Qt::AlignTop);

    //editorLayout->setSizeConstraint(QLayout::SetMinimumSize);

    saveButton = new QPushButton("Save");
    buttonsLayout->addWidget(saveButton, 1, 0);
    loadButton = new QPushButton("Load");
    buttonsLayout->addWidget(loadButton, 1, 1);
    moveButton = new QPushButton("Move");
    buttonsLayout->addWidget(moveButton, 2, 0);
    playButton = new QPushButton("Play");
    buttonsLayout->addWidget(playButton, 2, 1);
    loadMap();

    connect(loadButton, SIGNAL(clicked()), this, SLOT(loadMap()));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveMap()));

    connect(playButton, SIGNAL(clicked()), this, SLOT(startPlay()));
    connect(this, SIGNAL(winnerIs(Fraction)), this, SLOT(winner(Fraction)));
}

void GameWidget::winner(Fraction frac)
{

}

void GameWidget::startPlay()
{
    playButton->setEnabled(false);
}

void GameWidget::mousePressEvent(QMouseEvent *event)
{
    if (this->gameMap->getView()->underMouse())
    {
        if (event->button() == Qt::LeftButton)
        {
            if (Personage *pers = gameMap->personageAt(gameMap->globalToMapCoordinates(event->pos())))
            {
                if (pers->getPersFraction() == currentFractionsMove)
                {
                    if (settedPersonage)
                    {
                        gameMap->hidePersWay(settedPersonage);
                    }
                    settedPersonage = pers;
                    gameMap->drawPersWay(pers);
                }
                else
                {
                    if (settedPersonage)
                    {
                        gameMap->hidePersWay(settedPersonage);
                    }
                }
            }
        }
        if (event->button() == Qt::RightButton)
        {
            if (settedPersonage)
            {
                gameMap->buildWay(settedPersonage, gameMap->globalToMapCoordinates(event->pos()));
                gameMap->drawPersWay(settedPersonage);
            }
        }
    }
}

void GameWidget::keyPressEvent(QKeyEvent *event)
{
    Personage *pers = nullptr;
    if (event->key() == Qt::Key_Space && (currentPlayer == PLAYER) && settedPersonage)
    {
        if (settedPersonage->getWayToGo().size() != 0 && gameMap->personageAt(settedPersonage->getWayToGo().last())
                && gameMap->personageAt(settedPersonage->getWayToGo().last())->getPersFraction() != settedPersonage->getPersFraction())
            pers = gameMap->personageAt(settedPersonage->getWayToGo().last());
        gameMap->movePersonage(settedPersonage);
        if (pers)
        {
            fight(settedPersonage, pers);
        }
    }
}

Personage *GameWidget::fight(Personage *pers1, Personage *pers2)
{
    Personage *bluePers = (pers1->getPersFraction() == BLUE ? pers1 : pers2);
    Personage *looser = bluePers;
    if (settedPersonage == bluePers)
        settedPersonage = nullptr;
    gameMap->deletePersonage(bluePers);
}

void attackEnemy(Personage *pers)
{
//    for (int i = 0; i < )
}
