#pragma once

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QDesktopWidget>
#include <QSignalMapper>

#include "saverloader.h"



#include "mapfacade.h"

enum EditorState {OTHER, SURFACE, PROP, PERSONAGE};


class MapEditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MapEditorWidget(QWidget *parent = 0);
    ~MapEditorWidget();

    EditorState state;

    MapFacade *editMap;
    QGridLayout *buttonsLayout;
    QHBoxLayout *editorLayout;
    QPushButton *saveButton;
    QPushButton *loadButton;


    QPushButton *tree1Button;
    QPushButton *tree2Button;
    QPushButton *fieldButton;
    QPushButton *roadButton;
    QPushButton *swampButton;
    QPushButton *waterButton;
    QPushButton *rocksButton;
    QPushButton *persButton;
    QPushButton *cursorButton;

    QSignalMapper *surfMapper;
    QSignalMapper *propMapper;

    void mousePressEvent(QMouseEvent *event);
signals:

public slots:
    void changeToProp(int typeNum)
    {
        state = PROP;
        editMap->setPropFactoryType(static_cast<PropType>(typeNum));
    }
    void changeToSurface(int typeNum)
    {
        state = SURFACE;
        editMap->setSurfaceFactoryType(static_cast<SurfaceType>(typeNum));
    }
    void changeToPersonage()
    {
        state = PERSONAGE;
    }
    void changeToOther()
    {
        state = OTHER;
    }
    void saveMap()
    {
        MapFacadeSaveObject saveObj = editMap->saveToObject();
        SaverLoader saver;
        saver.save(saveObj);
    }
    void loadMap()
    {
        SaverLoader loader;
        MapFacadeSaveObject saveObj = loader.load();
        delete editMap;
        editMap = new MapFacade(saveObj, 29, this);
        this->editMap->show();
        editMap->getView()->show();
    }
};
