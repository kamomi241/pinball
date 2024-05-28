#pragma once

#include "Input.h"
#include "Vector2D.h"
#include "DxLib.h"

class Shooter {
public:
	Shooter();
	~Shooter();

	void initialize();
	void ballDraw();
	void draw();
	int updata();

	void setIsIn(bool);
private:
	int m_charge;
	Vector2D m_pos;
	int m_t;
	int m_vec;
	bool m_isInShooter;

	static int m_graph_base;
	static int m_SE;
	static int m_SE_charge;

};