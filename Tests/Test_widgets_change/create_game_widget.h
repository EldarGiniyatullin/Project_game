#pragma once

#include <QWidget>
#include <QImage>
#include <QApplication>
#include <QApplication>
#include <QPainter>
#include <QPushButton>
#include <QtMultimedia/QMediaPlayer>

#include "common_widget.h"


class CreateNewGameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CreateNewGameWidget(QWidget *parent = 0);
    QPushButton *main_menu_button;

protected:
    void paintEvent(QPaintEvent *)
    {
        QImage fontImage(":/Images/Menu_font_2.png");
        QPainter painter(this);
        painter.drawImage(0, 0, fontImage.scaled(this->size()));
    }

signals:
    void toMainMenuSignal();

public slots:
    void mainMenuButtonClicked()
    {
        emit toMainMenuSignal();
    }


};

