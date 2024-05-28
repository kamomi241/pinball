#pragma once

#include "Input.h"
#include "Vector2D.h"


class Ball {
public:
	Ball(Vector2D pos);
	~Ball();

	bool updata();
	void const draw();
	void push(Vector2D vec);
	
private:
	Vector2D m_pos;
	Vector2D m_vec;

	bool m_isDead;

	static int m_graph_ball;
	

};