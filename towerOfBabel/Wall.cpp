#include "Wall.h"
#include "Input.h"



SegmentWall::SegmentWall(Vector2D point1,Vector2D point2) :
	m_fakePointF(point1),
	m_fakePointL(point2)
{
	Vector2D a = point1 - point2;
	Vector2D normal(-a.y, a.x);
	normal = normal.normalizeVec() * -15;
	m_pointFirst = point1 + normal;
	m_pointLast = point2 + normal;
	if (SegmentWall::m_SE == 0)
		SegmentWall::m_SE = LoadSoundMem("effect\\wall.mp3");
}

SegmentWall::~SegmentWall() {}

void const SegmentWall::draw(unsigned int color) {
	DrawLineAA((float)m_pointFirst.x, (float)m_pointFirst.y, (float)m_pointLast.x, (float)m_pointLast.y, GetColor(255, 30, 30), 2);
	DrawLineAA((float)m_fakePointF.x, (float)m_fakePointF.y, (float)m_fakePointL.x, (float)m_fakePointL.y, color, 2);
	//DrawFormatString
	//DrawLineAA(m_pointFirst.x+10, m_pointFirst.y+10, m_pointLast.x+10, m_pointLast.y+10, color, 2);
}

void const SegmentWall::getPoint(Vector2D& pointF,Vector2D& pointL) {
	pointF = m_pointFirst;
	pointL = m_pointLast;
}


WallController::WallController() :
	m_drawingPointFirst(Vector2D()),
	m_drawingPointLast(Vector2D())
{
	m_lineColor = GetColor(250, 250, 250);
}

WallController::~WallController() {
	deleteWall();
}


void WallController::updata() {
	
	//デバッグ用
	/*
	Input* input = input->instance();
	if (input->isKeyDown(KEY_INPUT_W)) {
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
			printfDx("%.2f,%.2f^%.2f,%.2f ", m_drawingPointFirst.x, m_drawingPointFirst.y, m_drawingPointLast.x, m_drawingPointLast.y);
			m_listSegmentWall.emplace_back(new SegmentWall(m_drawingPointFirst, m_drawingPointLast));
			m_drawingPointFirst = Vector2D(0, 0);
			m_drawingPointLast = Vector2D(0, 0);
		}
	}


	if (input->isKeyPressed(KEY_INPUT_Q)) {
		deleteWall();
		loadWall();
	}
	DrawLineAA((float)m_drawingPointFirst.x, (float)m_drawingPointFirst.y, (float)m_drawingPointLast.x, (float)m_drawingPointLast.y, m_lineColor, 2);

	//ここまで
	*/
	
	
	for (auto itr = m_listSegmentWall.begin(); itr != m_listSegmentWall.end(); ++itr) {
		SegmentWall* wall = *itr;
		wall->draw(m_lineColor);
	}
	
}

void WallController::deleteWall() {
	for (auto itr = m_listSegmentWall.begin(); itr != m_listSegmentWall.end(); ++itr)
	{
		delete (*itr);
	}
	m_listSegmentWall.clear();
	m_drawingPointFirst = Vector2D();
	m_drawingPointLast = Vector2D();
}

std::vector<SegmentWall*> WallController::getList() {
	return m_listSegmentWall;
}

double SegmentWall::pointDiff(Vector2D p1,Vector2D p2){
	Vector2D wallVec = m_pointLast - m_pointFirst;
	Vector2D pVec = p2 - p1;
	double b = cross(p1 - m_pointFirst, p2 - m_pointFirst) / cross(wallVec, pVec);
	double crossX = m_pointFirst.x + b * (wallVec).x;//衝突位置を特定
	double crossY = m_pointFirst.y + b * (wallVec).y;
	double diff = (crossX - p1.x) * (crossX - p1.x) + (crossY - p1.y) * (crossY - p1.y);
	return diff;
}

void SegmentWall::updataPoint(Vector2D vf, Vector2D vl) {
	this->m_fakePointF = vf;
	this->m_fakePointL = vl;
	Vector2D a = vf - vl;
	Vector2D normal(-a.y, a.x);
	normal = normal.normalizeVec() * -15;
	this->m_pointFirst = vf + normal;
	this->m_pointLast = vl + normal;
}

double SegmentWall::reflectionBall(Vector2D& ballPos,Vector2D& ballVec, double buff) {
	Vector2D wallVec = m_pointLast - m_pointFirst;
	Vector2D playerNextPoint = ballPos + ballVec;
	double b = cross(ballPos - m_pointFirst, playerNextPoint - m_pointFirst) / cross(wallVec, ballVec);
	double crossX = m_pointFirst.x + b * (wallVec).x;//衝突位置を特定
	double crossY = m_pointFirst.y + b * (wallVec).y;
	Vector2D crossPoint(crossX, crossY);
	Vector2D newVec = crossPoint - ballPos;
	double power = ballVec.length();
	/*
	if (((m_pointFirst.y < m_pointLast.y && ballVec.x < 0) || (m_pointFirst.y > m_pointLast.y && ballVec.x > 0)) && ((power < 1.0 && abs(ballVec.x) < 0.1 ) || m_isRolled >0))
	{
		//printfDx("%f ", power);
		Vector2D normalVec(-wallVec.y, wallVec.x);
		normalVec.normalize();
		normalVec *= dot(newVec.inverse(), normalVec);
		if (ballVec.x < 0)
			wallVec;
		else
			wallVec = wallVec.inverse();
		if (power > abs((wallVec.x/wallVec.y) * 2))
		{
			power = abs((wallVec.x / wallVec.y) * 2);
		}
		wallVec = wallVec.normalizeVec() * abs(ballVec.x) * 1.1;
		ballVec = wallVec;
		ballPos = crossPoint + Vector2D(0.0, -0.001);
		if (m_isRolled == 2)
			m_isRolled = 2;
	}
	else */
	{
		Vector2D normalVec(-wallVec.y, wallVec.x);
		normalVec.normalize();
		normalVec *= dot(newVec.inverse(), normalVec);
		ballVec = normalVec + normalVec + newVec;
		if (power > 50.0)
			power = 50.0;
		ballVec = ballVec.normalizeVec() * power * 0.7;
		ballPos = crossPoint + (ballVec * 0.0001);
		if (ballVec.lengthSq() > 10)
			PlaySoundMem(m_SE, DX_PLAYTYPE_BACK);
		//DrawFormatString(330, 232, GetColor(250, 250, 250), "%.3f : %.3f", ballVec.x, ballVec.y);
		//	m_vec *= -1;
		return 0.0;
	}
}

/*
void SegmentWall::rollSet(bool b) {
	if (b == false) {
		if (m_isRolled > 0)
			m_isRolled -= 1;
	}
	else {
		if (m_isRolled > 0)
			m_isRolled = 2;
	}
}
*/


int SegmentWall::m_SE = 0;