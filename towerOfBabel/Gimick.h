#pragma once
#include "Input.h"
#include "Vector2D.h"
#include "DxLib.h"
#include "object.h"
#include <vector>



class GimickCircle : public Object {
public:
	GimickCircle(Vector2D center, double rad,double m_power);
	~GimickCircle() {}

	void draw();

	Vector2D getPoint();

	void setPoint(Vector2D p1);

	double pointDiff(Vector2D p1, Vector2D p2) override;
	double reflectionBall(Vector2D& ballPos, Vector2D& ballVec, double buf) override;


	bool BallCollide(Vector2D ballPos, Vector2D ballNextPos);

	void attackOff();

	bool getAttackSt();

private:
	Vector2D m_pos;

	double m_rad;

	double m_power;

	bool m_isAttack;

};


class GimickWall : public Object {
public:
	GimickWall(Vector2D point1, Vector2D point2);
	GimickWall() : m_pointFirst(), m_pointLast(),m_isAttack() {}
	~GimickWall();
	void const draw();
	void const getPoint(Vector2D& pointF, Vector2D& pointL);

	double pointDiff(Vector2D p1, Vector2D p2) override;
	double reflectionBall(Vector2D& ballPos, Vector2D& ballVec, double buff) override;

	bool BallCollide(Vector2D ballPos, Vector2D ballNextPos);

	void attackOff();
	bool getAttackSt();

private:
	Vector2D m_pointFirst;
	Vector2D m_pointLast;
	bool m_isAttack;
};


class GimickArea {
public:
	GimickArea(Vector2D pointF,Vector2D pointL,Vector2D pointFSub,Vector2D pointLSub);
	~GimickArea();

	bool BallCollide(Vector2D ballPos, Vector2D ballNextPos);
	void decCool();

	void draw();

	void attackOff();
	bool getAttackSt();
private:
	Vector2D m_pointFirst;
	Vector2D m_pointLast;
	Vector2D m_pointFirstSub;
	Vector2D m_pointLastSub;
	int m_coolTime;
	bool m_isAttack;
};

class DragonAttack {
public:
	DragonAttack();
	~DragonAttack();
	void draw();
	void updata();
	void reset(Vector2D pos, Vector2D vec,int life);

	void setDead();
	void setCoolTime(int time);
	int getCoolTime();

	bool collideCheck(Vector2D ballPos);
	Vector2D refrect(Vector2D ballpos);



private:
	Vector2D m_pos;
	Vector2D m_vec;
	double m_angle;
	int m_life;

	int m_coolTime;

	bool m_isDead;

	static int m_graph;
	static int m_SE;
	static int m_graph_effect[9];

};





class GimickController {
public:
	GimickController();
	~GimickController();

	int updata();
	void draw();
	void initialize();

	void setDragon();
	void setDragonNum(int num);

	void dragonReset();


	GimickCircle* getCircle(int);
	GimickWall* getWall(int);
	GimickArea* getArea();
	
	Vector2D collideDragonAttack(Vector2D ballPos);
	

private:
	GimickCircle* m_circle[3];
	GimickWall* m_wall[2];
	GimickArea* m_area;
	
	int m_attackNum;

	bool m_isDragon;
	int m_dragonNum;
	DragonAttack m_dragonAttack[8];

};