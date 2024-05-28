#pragma once

#include "Input.h"
#include "Vector2D.h"
#include "Wall.h"
#include "Flipper.h"
#include "object.h"
#include "Gimick.h"
#include "Input.h"
#include "DxLib.h"

class Ball {
public:
	Ball(Vector2D pos);
	~Ball();

	bool updata(WallController* wall,Flipper* flipper,GimickController* gimick);
	void const draw();
	void push(Vector2D vec);

	void setPos(Vector2D pos);

	void setShooter(bool);

	void setSpeedBuf(double d);
	
private:
	Vector2D m_pos;
	Vector2D m_vec;
	Vector2D m_refVec;

	double m_speedBuff;

	Vector2D m_push;

	//std::vector<SegmentWall*> m_listCollideSegmentWall;
	std::vector<Object*> m_list;//ƒŠƒXƒg‚ð‚±‚ê‚É•Ï‚¦‚é

	Object* m_collideObject;

	bool m_isDead;

	static int m_graph_ball;
	
	bool m_isInShooter;

	Vector2D m_drawingPointLast;
	Vector2D m_drawingPointFirst;

};