#pragma once

class GameObject
{
public:
    GameObject(QPixmap pixmap = QPixmap("://No_image.png"), bool isPassable = true)
        : objectPixmap(pixmap), isObjectPassable(isPassable) {}
    QPixmap objectPixmap;
    bool isObjectPassable;
    const QPixmap & getPixmap()
    {
        return objectPixmap;
    }
    bool isPassable()
    {
        return isObjectPassable;
    }

};
