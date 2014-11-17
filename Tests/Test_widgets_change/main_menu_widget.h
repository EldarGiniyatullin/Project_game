#pragma once

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>
#include <QPushButton>
#include <QtMultimedia/QMediaPlayer>
#include "common_widget.h"
#include "common_menu_resources.h"

class MainMenuWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainMenuWidget(QWidget *parent = 0);
    QPushButton *new_game_button;

protected:
    void paintEvent(QPaintEvent *)
    {
        QImage fontImage(":/Images/Menu_font.png");
        QPainter painter(this);
        painter.drawImage(0, 0, fontImage.scaled(this->size()));
    }

signals:
    void toCreateGameSignal();

public slots:
    void createGameButtonClicked()
    {
        emit toCreateGameSignal();
    }


};
