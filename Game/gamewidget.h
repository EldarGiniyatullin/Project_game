#pragma once

#include <QWidget>
#include <QMouseEvent>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "mapfacade.h"
#include "saverloader.h"
#include <widget.h>

enum PlayerIs{PLAYER, COMPUTER};

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = 0);

    Fraction currentFractionsMove;
    MapFacade *gameMap;
    QHBoxLayout *editorLayout;
    QGridLayout *buttonsLayout;
    QPushButton *saveButton;
    QPushButton *loadButton;
    QPushButton *moveButton;
    Personage *settedPersonage;
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    Personage *fight(Personage *pers1, Personage *pers2);
    PlayerIs redPlayer;
    PlayerIs bluePlayer;
    PlayerIs currentPlayer;
    void playBot(Fraction frac);
    void deletePersonage(Personage *pers);
    PlayerIs getPlayerIs(Fraction frac);
	int numberOfReds();
	int numberOfBLues();

signals:
    void winnerIs(Fraction frac);
public slots:
    void nextMove();
    void winner(Fraction frac);
    void saveMap()
    {
        MapFacadeSaveObject saveObj = gameMap->saveToObject();
        SaverLoader saver;
        saver.save(saveObj);
    }
    void loadMap()
    {
        SaverLoader loader;
        MapFacadeSaveObject saveObj = loader.load();
        if (gameMap)
            delete gameMap;
        gameMap = new MapFacade(saveObj, 29, this);
        this->settedPersonage = nullptr;
        this->currentFractionsMove = RED;
        this->gameMap->show();
        gameMap->getView()->show();
    }

};
