#include "saverloader.h"


SaverLoader::SaverLoader()
{
}

void SaverLoader::save(const MapFacadeSaveObject& object)
{
	//QFile file("C://Users/Inspiron/projectGame/Maps/" + object.name + ".txt");
    QFile file("C:/Progs/Project_game/Map editor/map.txt");
	file.remove();

	file.open(QIODevice::ReadWrite);

	QTextStream out(&file);


    out << object.numberOfPersonages << endl << object.xSquareNumber << endl << object.ySquareNumber << endl;


	for (int i = 0; i < object.numberOfPersonages; ++i)
	{
        out << object.personages[i].frac << endl << object.personages[i].spec << endl<< object.personages[i].xCoord << endl << object.personages[i].yCoord << endl;
	}

	for (int i = 0; i < object.xSquareNumber * object.ySquareNumber; ++i)
	{
        out << object.surfaces[i] << endl;
	}

	for (int i = 0; i < object.xSquareNumber * object.ySquareNumber; ++i)
	{
        out << object.props[i] << endl;
	}

	file.close();
}

MapFacadeSaveObject SaverLoader::load()
{
    QFile file("C:/Progs/Project_game/Map editor/map.txt");
	file.open(QIODevice::ReadWrite);

	MapFacadeSaveObject result;
	result.numberOfPersonages = QString(file.readLine()).toInt();
	result.xSquareNumber = QString(file.readLine()).toInt();
	result.ySquareNumber = QString(file.readLine()).toInt();

	for (int i = 0; i < result.numberOfPersonages; ++i)
	{

        Fraction frac = static_cast<Fraction>(QVariant(QString(file.readLine())).toInt());
        Speciality spec = static_cast<Speciality>(QVariant(QString(file.readLine())).toInt());
        int xCoord = static_cast<int>(QVariant(QString(file.readLine())).toInt());
        int yCoord = static_cast<int>(QVariant(QString(file.readLine())).toInt());
        MapFacadeSaveObject::SavedPersonage pers(frac, spec, xCoord, yCoord);
        result.personages.append(pers);
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
