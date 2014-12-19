#pragma once

#include "mapfacade.h"
#include <QByteArray>
#include <QTextStream>

class SaverLoader
{
public:
	SaverLoader();

    void save(const MapFacadeSaveObject &object);

	MapFacadeSaveObject load();

	//	void save(SaverLoaderObject object);

	//	SaverLoaderObject load(QFile file);
};
