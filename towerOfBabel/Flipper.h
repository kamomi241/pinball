#pragma once

#include "Input.h"
#include "Vector2D.h"
#include "DxLib.h"
#include <math.h>
#include "object.h"

class FlipperCircle : public Object {
public:
	FlipperCircle(Vector2D center,double rad);
	FlipperCircle():m_pos(),m_power(),m_rad() {}

	void draw();

	void const getPoint(Vector2D& p1);

	void setPoint(Vector2D p1);

	double pointDiff(Vector2D p1, Vector2D p2) override;
	double reflectionBall(Vector2D& ballPos, Vector2D& ballVec, double buff) override;

	void updataPower(double p);

	bool BallCollide(Vector2D ballPos, Vector2D ballNextPos);


private:
	Vector2D m_pos;;

	double m_rad;

	double m_power;
};




class FlipperRect : public Object {
public:
	FlipperRect(Vector2D p1, Vector2D p2, Vector2D p3, Vector2D p4,bool isLeft);
	FlipperRect(bool isLeft);
	FlipperRect():m_isLeft(),m_power() {}

	void draw();

	void const getPoint(Vector2D& p1, Vector2D& p2, Vector2D& p3,Vector2D& p4);

	void setPoint(Vector2D p1, Vector2D p2, Vector2D p3, Vector2D p4);

	double pointDiff(Vector2D p1, Vector2D p2) override;
	double reflectionBall(Vector2D& ballPos, Vector2D& ballVec, double buff) override;

	void updataPower(double p);

	bool BallCollide(Vector2D ballPos, Vector2D ballNextPos);


private:
	Vector2D m_point1;
	Vector2D m_point2;
	Vector2D m_point3;
	Vector2D m_point4;

	double m_power;

	bool m_isLeft;};



class Flipper {
public:
	Flipper(double leftX,double rightX,double Y);
	~Flipper();
	void initialize();
	void updata();
	void draw();
	void setReverse(char c);

	FlipperCircle* const getCircle(int num);//numが左から1,2,3,4
	FlipperRect* const getRect(int num);//numが1なら左、それ以外は右

private:
	
	double m_radRight;
	double m_radLeft;

	Vector2D m_posRight;
	Vector2D m_posLeft;

	double m_radPowerRight;
	double m_radPowerLeft;

	char m_Reverse;//0通常　1左右逆　2上下逆　3左右上下逆 4

	FlipperCircle* m_rightMoCircle;
	FlipperCircle* m_leftMoCircle;
	FlipperCircle* m_rightCircle;
	FlipperCircle* m_leftCircle;
	FlipperRect* m_rightRect;
	FlipperRect* m_leftRect;

	int m_graph_flipper;

	static int m_SE;
	
};