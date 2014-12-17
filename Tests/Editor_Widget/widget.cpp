#include "widget.h"
#include "ui_widget.h"
#include <qlayout.h>
#include <qpushbutton.h>
#include <QSpacerItem>
#include <QLabel>

Widget::Widget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Widget)
{
	ui->setupUi(this);

	QHBoxLayout *editorLayout = new QHBoxLayout;
	this->setLayout(editorLayout);

	QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);
	editorLayout->addSpacerItem(spacer);

	QGridLayout *buttonLayout = new QGridLayout;

	QWidget *palitre = new QWidget;
	palitre->setLayout(buttonLayout);
	palitre->setFixedHeight(250);
	palitre->setFixedWidth(250);
	editorLayout->addWidget(palitre);

	//editorLayout->setSizeConstraint(QLayout::SetMinimumSize);

	QLabel *label = new QLabel("Surfaces");
	buttonLayout->addWidget(label, 0, 0);
	QPushButton *noImButton = new QPushButton("Nothing");
	buttonLayout->addWidget(noImButton, 1, 0);
	QPushButton *waterButton = new QPushButton("Water");
	buttonLayout->addWidget(waterButton, 1, 1);
	QPushButton *fieldsButton = new QPushButton("Fields");
	buttonLayout->addWidget(fieldsButton, 2, 0);
	QPushButton *rocksButton = new QPushButton("Rocks");
	buttonLayout->addWidget(rocksButton, 2, 1);
	QPushButton *roadButton = new QPushButton("Road");
	buttonLayout->addWidget(roadButton, 3, 0);
	QPushButton *swampButton = new QPushButton("Swamp");
	buttonLayout->addWidget(swampButton, 3, 1);

	QLabel *label2 = new QLabel("Props");
	buttonLayout->addWidget(label2, 4, 0);
	QPushButton *nullButton = new QPushButton("Nothing");
	buttonLayout->addWidget(nullButton, 5, 0);
	QPushButton *tree1Button = new QPushButton("Tree1");
	buttonLayout->addWidget(tree1Button, 5, 1);
	QPushButton *tree2Button = new QPushButton("Tree2");
	buttonLayout->addWidget(tree2Button, 5, 2);

	QLabel *label3 = new QLabel("Some stuff");
	buttonLayout->addWidget(label3, 6, 0);
	QPushButton *persButton = new QPushButton("Personage");
	buttonLayout->addWidget(persButton, 7, 0);
	QPushButton *cursorButton = new QPushButton("Cursor");
	buttonLayout->addWidget(cursorButton, 7, 1);

//	QSpacerItem *spacer2 = new QSpacerItem(0,500, QSizePolicy::Expanding, QSizePolicy::Fixed);
//	buttonLayout->addItem(spacer2, 8, 3);

	connect(noImButton, SIGNAL(clicked()), this, SLOT(changeTypeToSurf()));
	connect(waterButton, SIGNAL(clicked()), this, SLOT(changeTypeToSurf()));
	connect(fieldsButton, SIGNAL(clicked()), this, SLOT(changeTypeToSurf()));
	connect(rocksButton, SIGNAL(clicked()), this, SLOT(changeTypeToSurf()));
	connect(roadButton, SIGNAL(clicked()), this, SLOT(changeTypeToSurf()));
	connect(swampButton, SIGNAL(clicked()), this, SLOT(changeTypeToSurf()));

	connect(nullButton, SIGNAL(clicked()), this, SLOT(changeTypeToProps()));
	connect(tree1Button, SIGNAL(clicked()), this, SLOT(changeTypeToProps()));
	connect(tree2Button, SIGNAL(clicked()), this, SLOT(changeTypeToProps()));

	connect(persButton, SIGNAL(clicked()), this, SLOT(changeTypeToStuff()));
	connect(cursorButton, SIGNAL(clicked()), this, SLOT(changeTypeToStuff()));
}

Widget::~Widget()
{
	delete ui;
}

void Widget::changeTypeToProps()
{
	type = PROPS;
}

void Widget::changeTypeToSurf()
{
	type = SURFACE;
}

void Widget::changeTypeToStuff()
{
	type = SOMESTUFF;
}

