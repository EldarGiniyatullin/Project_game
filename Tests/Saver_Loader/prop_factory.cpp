#include "prop_factory.h"



PropObject *PropFactory::clone(qreal priority)
{
    PropObject *newObj(this->clone());
    newObj->setDrawingPriority(priority);
    return newObj;
}


PropObject *PropFactory::clone()
{
    return clone(currentType);
}


PropObject *PropFactory::clone(PropType type)
{
    return (type == NULLOBJECT ? nullptr : new PropObject(map.value(type)));
}


PropObject *PropFactory::clone(PropType type, qreal priority)
{
    PropObject *newObj(this->clone(type));
    newObj->setDrawingPriority(priority);
    return newObj;
}
