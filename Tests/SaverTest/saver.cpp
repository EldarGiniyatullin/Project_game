#include "saver.h"
#include <QVector>
#include "project_objects.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "QByteArray"

Saver::Saver()
{
}

void Saver::save()
{
	int size = 2;
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
	cells[1][0] = new GameObject();
	cells[1][1] = new GameObject();

	QFile file("C://Users/Inspiron/projectGame/Maps/map.txt");
	file.remove();

	file.open(QIODevice::ReadWrite);

	QTextStream out(&file);

	out << size;
	out << '\n';

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			out << cells[i][j]->objectType() << '\n';
		}

	file.close();
//	file.open(QIODevice::ReadWrite);

//	int testSize = file.readLine().toInt();

//	qDebug() << testSize;

//	QString testString;

//	for (int i = 0; i < size; i++)
//		for (int j = 0; j < size; j++)
//		{
//			testString = file.readLine();
//			qDebug() << testString;
//		}

//	file.close();
}
