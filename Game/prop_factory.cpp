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
    PropObject *newObj(new PropObject(map.value(type)));
    return newObj;
}


PropObject *PropFactory::clone(PropType type, qreal priority)
{
    PropObject *newObj(this->clone(type));
    newObj->setDrawingPriority(priority);
    return newObj;
}
