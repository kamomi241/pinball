#pragma once
#include "Vector2D.h"

class Object {
public:
	Object();
	~Object();
	void setPoint(double diffSq);
	double getPoint();
	bool getIsCollide();
	void reset();
	virtual double pointDiff(Vector2D p1, Vector2D p2) { return 0.0; }//衝突点とボールの距離を返す。
	virtual double reflectionBall(Vector2D& ballPos, Vector2D& ballVec, double buff) { return 0.0; }//反射処理
private:
	bool m_isCollide;
	double m_diffSq;
};
