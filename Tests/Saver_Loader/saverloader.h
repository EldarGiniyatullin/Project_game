#pragma once

#include "mapfacade_save_object.h"
#include <QByteArray>

class SaverLoader
{
public:
	SaverLoader();

	void save(MapFacadeSaveObject object);

	MapFacadeSaveObject load();

	//	void save(SaverLoaderObject object);

	//	SaverLoaderObject load(QFile file);
};
