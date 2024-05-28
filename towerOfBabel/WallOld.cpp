#include "Wall.h"
#include "Input.h"
#include "DxLib.h"



SegmentWall::SegmentWall(Vector2D point1,Vector2D point2) :
	m_pointFirst(point1),
	m_pointLast(point2)
{
}

SegmentWall::~SegmentWall() {}

void const SegmentWall::draw(unsigned int color) {
	DrawLineAA(m_pointFirst.x, m_pointFirst.y, m_pointLast.x, m_pointLast.y, color, 2);
	//double angle = 
	//DrawFormatString
}



WallController::WallController() :
	m_drawingPointFirst(Vector2D()),
	m_drawingPointLast(Vector2D())
{
	m_lineColor = GetColor(250, 250, 250);
}

WallController::~WallController() {
	m_listSegmentWall.clear();
}


void WallController::updata() {
	Input* input = input->instance();
	Vector2D mousevec = input->getMouseVector();
	if (input->isMousePressed(MOUSE_INPUT_LEFT))
	{
		m_drawingPointFirst = mousevec;
		m_drawingPointLast = mousevec;
	}
	else if (input->isMouseKeepPressing(MOUSE_INPUT_LEFT))
	{
		m_drawingPointLast = mousevec;
	}
	else if (input->isMouseReleased(MOUSE_INPUT_LEFT))
	{
		m_listSegmentWall.emplace_back(new SegmentWall(m_drawingPointFirst, m_drawingPointLast));
	}
	if (input->isKeyPressed(KEY_INPUT_Q)) {
		deleteWall();
	}
	DrawLineAA(m_drawingPointFirst.x, m_drawingPointFirst.y, m_drawingPointLast.x, m_drawingPointLast.y, m_lineColor, 2);
	for (auto itr = m_listSegmentWall.begin(); itr != m_listSegmentWall.end(); ++itr) {
		SegmentWall* wall = *itr;
		wall->draw(m_lineColor);
	}
}

void WallController::deleteWall() {
	m_listSegmentWall.clear();
	m_drawingPointFirst = Vector2D();
	m_drawingPointLast = Vector2D();
}
