#include "mapeditorwidget.h"
#include <QApplication>

MapEditorWidget::MapEditorWidget(QWidget *parent) :
    editMap(new MapFacade(40, 40, 29, this)),
    QWidget(parent)
{

    editorLayout = new QHBoxLayout(this);

//    editorLayout->addWidget(editMap->getView());
    buttonsLayout = new QGridLayout;

    QWidget *palitre = new QWidget;
    palitre->setLayout(buttonsLayout);
    palitre->setFixedHeight(300);
    palitre->setFixedWidth(250);
    editorLayout->addWidget(palitre, 0, Qt::AlignRight | Qt::AlignTop);

    //editorLayout->setSizeConstraint(QLayout::SetMinimumSize);

    QLabel *label = new QLabel("Surfaces");
    buttonsLayout->addWidget(label, 0, 0);
    waterButton = new QPushButton("Water");
    buttonsLayout->addWidget(waterButton, 1, 0);
    fieldButton = new QPushButton("Fields");
    buttonsLayout->addWidget(fieldButton, 1, 1);
    rocksButton = new QPushButton("Rocks");
    buttonsLayout->addWidget(rocksButton, 2, 0);
    roadButton = new QPushButton("Road");
    buttonsLayout->addWidget(roadButton, 2, 1);
    swampButton = new QPushButton("Swamp");
    buttonsLayout->addWidget(swampButton, 3, 0);

    QLabel *label2 = new QLabel("Props");
    buttonsLayout->addWidget(label2, 4, 0);
    tree1Button = new QPushButton("Tree1");
    buttonsLayout->addWidget(tree1Button, 5, 0);
    tree2Button = new QPushButton("Tree2");
    buttonsLayout->addWidget(tree2Button, 5, 1);

    QLabel *label3 = new QLabel("Some stuff");
    buttonsLayout->addWidget(label3, 6, 0);
    persButton = new QPushButton("Personage");
    buttonsLayout->addWidget(persButton, 7, 0);
    cursorButton = new QPushButton("Cursor");
    buttonsLayout->addWidget(cursorButton, 7, 1);

    QLabel *label4 = new QLabel("Save/Load");
    buttonsLayout->addWidget(label4, 8, 0);
    saveButton = new QPushButton("Save", this);
    buttonsLayout->addWidget(saveButton, 9, 0);
    loadButton = new QPushButton("Load", this);
    buttonsLayout->addWidget(loadButton, 9, 1);


    state = OTHER;


    surfMapper = new QSignalMapper(this);
    propMapper = new QSignalMapper(this);

    connect(tree1Button, SIGNAL(clicked()), propMapper, SLOT(map()));
    connect(tree2Button, SIGNAL(clicked()), propMapper, SLOT(map()));

    propMapper->setMapping(tree1Button, 1);
    propMapper->setMapping(tree2Button, 2);
    connect(propMapper, SIGNAL(mapped(int)), this, SLOT(changeToProp(int)));

    connect(fieldButton, SIGNAL(clicked()), surfMapper, SLOT(map()));
    connect(roadButton, SIGNAL(clicked()), surfMapper, SLOT(map()));
    connect(waterButton, SIGNAL(clicked()), surfMapper, SLOT(map()));
    connect(rocksButton, SIGNAL(clicked()), surfMapper, SLOT(map()));
    connect(swampButton, SIGNAL(clicked()), surfMapper, SLOT(map()));


    surfMapper->setMapping(fieldButton, 1);
    surfMapper->setMapping(roadButton, 2);
    surfMapper->setMapping(waterButton, 3);
    surfMapper->setMapping(rocksButton, 4);
    surfMapper->setMapping(swampButton, 5);
    connect(surfMapper, SIGNAL(mapped(int)), this, SLOT(changeToSurface(int)));

    connect(persButton, SIGNAL(clicked()), this, SLOT(changeToPersonage()));
    connect(cursorButton, SIGNAL(clicked()), this, SLOT(changeToOther()));

    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveMap()));
    connect(loadButton, SIGNAL(clicked()), this, SLOT(loadMap()));
}

MapEditorWidget::~MapEditorWidget()
{
    delete editMap;
    delete buttonsLayout;

    delete saveButton;
    delete loadButton;


    delete tree1Button;
    delete tree2Button;
    delete fieldButton;
    delete roadButton;
    delete swampButton;
    delete waterButton;
    delete rocksButton;
    delete persButton;
    delete cursorButton;

    delete surfMapper;
    delete propMapper;
}

void MapEditorWidget::mousePressEvent(QMouseEvent *event)
{
    if (this->editMap->getView()->underMouse())
    {
        if (event->button() == Qt::LeftButton)
        {
            switch (state)
            {
            case PROP:
                editMap->addPropFromMouse(event);
                break;
            case SURFACE:
                editMap->addSurfaceFromMouse(event);
                break;
            case PERSONAGE:
                editMap->addPersonageFromMouse(event, GREEN, WARRIOR);
                break;
            case OTHER:
                break;
            default:
                break;
            }
        }
        else if (event->button() == Qt::RightButton)
        {
            if (Personage *pers = editMap->personageUnderMouse(event))
                editMap->deletePersonage(pers);
            else
            {
                QPoint point = editMap->globalToMapCoordinates(event->pos());
                editMap->addPropObject(NULLOBJECT, point.x(), point.y());
            }
        }
    }
}
