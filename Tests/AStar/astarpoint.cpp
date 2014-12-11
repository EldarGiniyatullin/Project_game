#include "astarpoint.h"

AStarPoint::AStarPoint()
{
	parent = NULL;
	closed = false;
	opened = false;

	x = 0;
	y = 0;
	f = 0;
	g = 0;
	h = 0;
}

AStarPoint::AStarPoint(QPoint point, bool w)
{
	parent = NULL;
	closed = false;
	opened = false;

	f = 0;
	g = 0;
	h = 0;

	this->walkable = w;
	this->x = point.x();
	this->y = point.y();
}

QPoint* AStarPoint::getPosition()
{
	return new QPoint(this->x, this->y);
}

int AStarPoint::getX()
{
	return x;
}

int AStarPoint::getY()
{
	return y;
}

AStarPoint* AStarPoint::getParent()
{
	return parent;
}

void AStarPoint::setParent(AStarPoint *p)
{
	parent = p;
}

bool AStarPoint::hasParent()
{
	return parent != NULL;
}

void AStarPoint::computeScores(AStarPoint *end)
{
	g = getGScore(parent);
	h = getHScore(end);
	f = g + h;
}

int AStarPoint::getGScore(AStarPoint *p)
{
	return p->g + ((x == p->x || y == p->y) ? 10 : 14);
}

int AStarPoint::getHScore(AStarPoint *p)
{
	return (abs(p->x - x) + abs(p->y - y)) * 10;
}

int AStarPoint::getGScore()
{
	return g;
}

int AStarPoint::getFScore()
{
	return f;
}

float AStarPoint::getXf()
{
	return (float)x;
}

float AStarPoint::getYf()
{
	return (float)y;
}
