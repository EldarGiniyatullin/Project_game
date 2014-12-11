#pragma once

#include <QPixmap>
#include <QGraphicsItem>
#include <QString>

//примерно

//for save
class GameObject
{
public:
	GameObject(QPixmap pixmap = QPixmap("://No_image.png"), bool isPassable = true)
		: objectPixmap(pixmap), isPassable(isPassable), name("basicObject") {}

	QString name;

	QPixmap objectPixmap;
	bool isPassable;

	const QPixmap & getPixmap()
	{
		return objectPixmap;
	}

	bool isObjectPassable()
	{
		return isPassable;
	}

	QString objectType()
	{
		return name;
	}

};

class TreeObject : public GameObject
{
public:
	TreeObject() : GameObject(QPixmap("://Little_tree.png"), false)   {name = "tree";}

};

// after conversion
//      ||
//      ||
//      \/
//for map

class MapObject
{
public:
	MapObject(GameObject object) : baseGameObject(object),
		objectPixmapItem(new QGraphicsPixmapItem(object.getPixmap()))
	{}
	GameObject baseGameObject;
	QGraphicsPixmapItem *objectPixmapItem;
};

