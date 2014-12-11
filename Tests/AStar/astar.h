#include "project_objects.h"
#include <QList>
#include <QPoint>
#include <QVector>
#include <astarpoint.h>

class AStar
{
public:
	AStar();

	QList<QPoint *> calcualtePath(QPoint start, QPoint endp);

	void addCells(QVector<QVector<GameObject *> > cells);

private:
	QMap <int, QMap <int, AStarPoint*> > AStarCells;

	AStarPoint *getPoint(QPoint point);
	AStarPoint *getPointFromCoord(QPoint coord);

	bool pointExists(QPoint point);
	bool pointIsWalkable(QPoint point);
};
