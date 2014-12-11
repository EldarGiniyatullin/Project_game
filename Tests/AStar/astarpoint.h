#include <QPoint>

class AStarPoint
{
public:

	AStarPoint();
	AStarPoint(QPoint point, bool w);

	QPoint* getPosition();
	int getX();
	int getY();

	AStarPoint* getParent();
	void setParent(AStarPoint *p);
	bool hasParent();

	void computeScores(AStarPoint *end);
	int getGScore(AStarPoint *p);
	int getHScore(AStarPoint *p);
	int getGScore();
	int getFScore();

	float getXf();
	float getYf();

	bool walkable;
	bool closed;
	bool opened;

private :
	int x;
	int y;

	unsigned int f;
	unsigned int g;
	unsigned int h;

	AStarPoint *parent;

};
