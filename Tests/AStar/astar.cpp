#include "astar.h"

AStar::AStar()
{
}

void AStar::addCells(QVector<QVector<GameObject *> > cells)
{
	for (int i = 0; i < cells.size(); i++)
	{
		for (int j = 0; j < cells[i].size(); j++)
		{
			AStarCells[i][j] = new AStarPoint(QPoint(i, j), cells[i][j]->isPassable);
		}
	}
}

AStarPoint *AStar::getPoint(QPoint point)
{
	if (pointExists(point))
	{
		return AStarCells[point.x()][point.y()];
	}
	else
	{
		return new AStarPoint(QPoint(0, 0), false);
	}
}

AStarPoint *AStar::getPointFromCoord(QPoint coord)
{
	return getPoint(coord);
}

bool AStar::pointExists(QPoint point)
{
	return (point.x() >= 0 && point.y() >=0 && point.x() < AStarCells.size() && point.y() < AStarCells.size());
}

bool AStar::pointIsWalkable(QPoint point)
{
	return (pointExists(point) && AStarCells[point.x()][point.y()]->walkable);
}


QList<QPoint *> AStar::calcualtePath(QPoint startp, QPoint endp)
{
	QList<QPoint*> path;

	AStarPoint *start = getPointFromCoord(startp);
	AStarPoint *end = getPointFromCoord(endp);
	AStarPoint *current;
	AStarPoint *child;

	QList<AStarPoint*> openList;
	QList<AStarPoint*> closedList;
	QList<AStarPoint*>::iterator i;

	unsigned int n = 0;

	openList.push_back(start);
	start->opened = true;

	while (n == 0 || (current != end && n < 50))
	{
		for (i = openList.begin(); i != openList.end(); ++i)
		{
			if (i == openList.begin() || (*i)->getFScore() <= current->getFScore())
			{
				current = (*i);
			}
		}

		if (current == end)
		{
			break;
		}

		openList.removeOne(current);
		current->opened = false;

		closedList.push_back(current);
		current->closed = true;

		for (int x = -1; x < 2; x++)
		{
			for (int y = -1; y < 2; y++)
			{
				if (x == 0 && y == 0)
				{
					continue;
				}

				child = getPoint(QPoint(current->getX() + x, current->getY() + y));

				if (child->closed || !child->walkable)
				{
					continue;
				}

				if (x != 0 && y != 0)
				{
					if (!pointIsWalkable(QPoint(current->getX(), current->getY() + y)) || getPoint(QPoint(current->getX(), current->getY() + y))->closed)
					{
						continue;
					}

					if (!pointIsWalkable(QPoint(current->getX() + x, current->getY())) || getPoint(QPoint(current->getX() + x, current->getY()))->closed)
					{
						continue;
					}
				}

				if (child->opened)
				{
					if (child->getGScore() > child->getGScore(current))
					{
						child->setParent(current);
						child->computeScores(end);
					}
				}
				else
				{
					openList.push_back(child);
					child->opened = true;

					child->setParent(current);
					child->computeScores(end);
				}
			}
		}

		n ++;
	}

	for (i = openList.begin(); i != openList.end(); ++i)
	{
		(*i)->opened = false;
	}
	for (i = closedList.begin(); i != closedList.end(); ++i)
	{
		(*i)->closed = false;
	}

	while (current->hasParent() && current != start)
	{
		path.push_back(current->getPosition());
		current = current->getParent();
		n++;
	}

	return path;
}
