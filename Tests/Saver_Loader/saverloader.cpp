#include "saverloader.h"

SaverLoader::SaverLoader()
{
}

void SaverLoader::save(MapFacadeSaveObject object)
{
	//QFile file("C://Users/Inspiron/projectGame/Maps/" + object.name + ".txt");
	QFile file("C://Users/Inspiron/projectGame/Maps/map.txt");
	file.remove();

	file.open(QIODevice::ReadWrite);

	QTextStream out(&file);

	out << object.numberOfPersonages << '\n' << object.xSquareNumber << '\n' << object.ySquareNumber << '\n';


	for (int i = 0; i < object.numberOfPersonages; ++i)
	{
		out << (int)object.personages[i].frac << '\n' << (int)object.personages[i].spec << '\n';
	}

	for (int i = 0; i < object.xSquareNumber * object.ySquareNumber; ++i)
	{
		out << (int)object.surfaces[i] << '\n';
	}

	for (int i = 0; i < object.xSquareNumber * object.ySquareNumber; ++i)
	{
		out << (int)object.props[i] << '\n';
	}

	file.close();
}

MapFacadeSaveObject SaverLoader::load()
{
	QFile file("C://Users/Inspiron/projectGame/Maps/map.txt");
	file.open(QIODevice::ReadWrite);

	MapFacadeSaveObject result;
	result.numberOfPersonages = QString(file.readLine()).toInt();
	result.xSquareNumber = QString(file.readLine()).toInt();
	result.ySquareNumber = QString(file.readLine()).toInt();

	for (int i = 0; i < result.numberOfPersonages; ++i)
	{
		result.personages[i].frac = static_cast<Fraction>(QVariant(QString(file.readLine())).toInt());
		result.personages[i].spec = static_cast<Speciality>(QVariant(QString(file.readLine())).toInt());
	}

	for (int i = 0; i < result.xSquareNumber * result.ySquareNumber; ++i)
	{
		result.surfaces.append(static_cast<SurfaceType>(QVariant(QString(file.readLine())).toInt()));
	}

	for (int i = 0; i < result.xSquareNumber * result.ySquareNumber; ++i)
	{
		result.props.append(static_cast<PropType>(QVariant(QString(file.readLine())).toInt()));
	}

	return result;
}

//void SaverLoader::save(SaverLoaderObject object)
//{
//	QFile file("C://Users/Inspiron/projectGame/Maps/" + object.name + ".txt");
//	file.remove();

//	file.open(QIODevice::ReadWrite);

//	QTextStream out(&file);

//	out << object.numberOfPers << '\n' << object.x << '\n' << object.y << '\n';


//	for (int i = 0; i < object.numberOfPers; ++i)
//	{
//		out << (int)object.perses[i].faction << '\n' << (int)object.perses[i].spec << '\n';
//	}

//	for (int i = 0; i < object.x * object.y; ++i)
//	{
//		out << (int)object.surs[i] << '\n';
//	}

//	for (int i = 0; i < object.x * object.y; ++i)
//	{
//		out << (int)object.props[i] << '\n';
//	}

//	file.close();
//}

//SaverLoaderObject SaverLoader::load(QFile file)
//{
//	SaverLoaderObject result;
//	result.numberOfPers = QString(file.readLine()).toInt();
//	result.x = QString(file.readLine()).toInt();
//	result.y = QString(file.readLine()).toInt();

//	for (int i = 0; i < result.numberOfPers; ++i)
//	{
//		result.perses[i].faction = static_cast<Fraction>(QVariant(QString(file.readLine())).toInt());
//		result.perses[i].spec = static_cast<Speciality>(QVariant(QString(file.readLine())).toInt());
//	}

//	for (int i = 0; i < result.x * result.y; ++i)
//	{
//		result.surs.append(static_cast<SurfaceType>(QVariant(QString(file.readLine())).toInt()));
//	}

//	for (int i = 0; i < result.x * result.y; ++i)
//	{
//		result.props.append(static_cast<PropType>(QVariant(QString(file.readLine())).toInt()));
//	}

//	return result;
//}
