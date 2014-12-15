#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Widget)
{
	ui->setupUi(this);

	type = NOTHING;

	connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(changeTypeToSurf()));
	connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(changeTypeToSurf()));
	connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(changeTypeToSurf()));
	connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(changeTypeToSurf()));
	connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(changeTypeToSurf()));
	connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(changeTypeToSurf()));

	connect(ui->pushButton_11, SIGNAL(clicked()), this, SLOT(changeTypeToProps()));
	connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(changeTypeToProps()));
	connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(changeTypeToProps()));

	connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(changeTypeToStuff()));
	connect(ui->pushButton_10, SIGNAL(clicked()), this, SLOT(changeTypeToStuff()));
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
