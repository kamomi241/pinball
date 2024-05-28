#pragma once
#include <vector>
#include"Vector2D.h"
#include "object.h"
#include "DxLib.h"




class SegmentWall : public Object{
public:
	SegmentWall(Vector2D point1,Vector2D point2);
	SegmentWall() : m_pointFirst(),m_pointLast(),m_fakePointF(),m_fakePointL(){}
	~SegmentWall();
	void const draw(unsigned int color);
	void const getPoint(Vector2D& pointF, Vector2D& pointL);
	void updataPoint(Vector2D vf, Vector2D vl); //‚±‚±‚©‚ç

	double pointDiff(Vector2D p1,Vector2D p2) override;
	double reflectionBall(Vector2D& ballPos,Vector2D& ballVec, double buff) override;
	
	//void rollSet(bool b);
private:
	Vector2D m_pointFirst;
	Vector2D m_pointLast;

	Vector2D m_fakePointF;
	Vector2D m_fakePointL;

//	int m_isRolled;

	static int m_SE;
};


class WallController {
public:
	WallController();
	~WallController();
	void updata();
	void deleteWall();

	std::vector<SegmentWall*> getList();

	void loadWall();
private:
	Vector2D m_drawingPointFirst;
	Vector2D m_drawingPointLast;
	unsigned m_lineColor;

	std::vector<SegmentWall*> m_listSegmentWall;

};