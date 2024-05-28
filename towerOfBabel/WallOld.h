#pragma once
#include <vector>
#include"Vector2D.h"




class SegmentWall {
public:
	SegmentWall(Vector2D point1,Vector2D point2);
	~SegmentWall();
	void const draw(unsigned int color);
private:
	Vector2D m_pointFirst;
	Vector2D m_pointLast;
};


class WallController {
public:
	WallController();
	~WallController();
	void updata();
	void deleteWall();
private:
	Vector2D m_drawingPointFirst;
	Vector2D m_drawingPointLast;
	unsigned m_lineColor;

	std::vector<SegmentWall*> m_listSegmentWall;
};