#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Widget)
{
	ui->setupUi(this);

	int size = 3;
	QVector<QVector< GameObject *> > cells;

	cells = QVector<QVector <GameObject*> > (size);
	for (int i = 0; i < cells.size(); i++)
	{
		cells[i] = QVector <GameObject*> (size);
		for (int j = 0; j < cells[i].size(); j++)
		{
			cells[i][j] = nullptr;
		}
	}

	cells[0][0] = new GameObject();
	cells[0][1] = new TreeObject();
	cells[0][2] = new TreeObject();
	cells[1][0] = new GameObject();
	cells[1][1] = new GameObject();
	cells[1][2] = new GameObject();
	cells[2][0] = new GameObject();
	cells[2][1] = new GameObject();
	cells[2][2] = new GameObject();

	AStar *astar = new AStar();
	astar->addCells(cells);

	QList<QPoint *> path = astar->calcualtePath(QPoint(0, 0), QPoint(2, 2));

	QList<QPoint *>::iterator i;

	for (i = path.begin(); i != path.end(); ++i)
		qDebug() << (*i)->x() << (*i)->y() << '\n';
}

Widget::~Widget()
{
	delete ui;
}
