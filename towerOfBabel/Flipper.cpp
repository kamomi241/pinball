#include "Flipper.h"

Flipper::Flipper(double leftX, double rightX, double Y) :
	m_radLeft(0.0),
	m_radRight(0.0),
	m_radPowerLeft(0.0),
	m_radPowerRight(0.0),
	m_posRight(rightX, Y),
	m_posLeft(leftX, Y),
	m_rightMoCircle(),
	m_leftMoCircle(),
	m_rightCircle(),
	m_leftCircle(),
	m_rightRect(),
	m_leftRect(),
	m_Reverse(0)
{
	m_graph_flipper = LoadGraph("texture\\flipper.png");
	if (Flipper::m_SE == 0)
		Flipper::m_SE = LoadSoundMem("effect\\flipper.mp3");
}


Flipper::~Flipper() {
	delete m_rightRect;
	delete m_leftRect;
	delete m_rightCircle;
	delete m_leftCircle;
	delete m_rightMoCircle;
	delete m_leftMoCircle;
}

void Flipper::initialize() {
	m_radLeft = 1.5;
	m_radRight = -1.5;
	m_radPowerLeft = 0.0;
	m_radPowerRight = 0.0;
	m_Reverse = 0;
	m_rightCircle =new FlipperCircle(m_posRight,20.0);
	m_leftCircle =new FlipperCircle(m_posLeft, 20.0);
	m_rightMoCircle = new FlipperCircle(m_posRight, 15.0);
	m_leftMoCircle = new FlipperCircle(m_posLeft, 15.0);
	m_rightRect = new FlipperRect(false);
	m_leftRect = new FlipperRect(true);

	//角度からフリッパーを生成
	double cosR = cos(m_radRight - 1.5707);
	double sinR = sin(m_radRight - 1.5707);
	Vector2D p3 = m_posRight + Vector2D((-5.0 * cosR) - (20 * sinR), (-5.0 * sinR) + (cosR * 20.0));
	Vector2D p2 = m_posRight + Vector2D((-5.0 * cosR) + (20 * sinR), (-5.0 * sinR) - (cosR * 20.0));
	Vector2D center = m_posRight + Vector2D(60 * cos(m_radRight - 1.5707), 60 * sin(m_radRight - 1.5707));
	Vector2D p4 = m_posRight + Vector2D((60.0 * cosR) - (15 * sinR), (60.0 * sinR) + (cosR * 15.0));
	Vector2D p1 = m_posRight + Vector2D((60.0 * cosR) + (15 * sinR), (60.0 * sinR) - (cosR * 15.0));
	m_rightRect->setPoint(p1, p2, p3, p4);
	m_rightMoCircle->setPoint(center);

	//角度からフリッパーを生成
	double cosL = cos(m_radLeft - 1.5707);
	double sinL = sin(m_radLeft - 1.5707);
	Vector2D pl1 = m_posLeft + Vector2D((-5.0*cosL) - (20 * sinL),(- 5.0 * sinL) + (cosL * 20.0));
	Vector2D pl4 = m_posLeft + Vector2D(( - 5.0 * cosL) + (20 * sinL), (-5.0 * sinL) - (cosL * 20.0));
	Vector2D centerl = m_posLeft + Vector2D(60 * cos(m_radLeft - 1.5707), 60 * sin(m_radLeft - 1.5707));
	Vector2D pl2 = m_posLeft + Vector2D((60.0 * cosL) - (15 * sinL), (60.0 * sinL) + (cosL * 15.0));
	Vector2D pl3 = m_posLeft + Vector2D((60.0 * cosL) + (15 * sinL), (60.0 * sinL) - (cosL * 15.0));
	m_leftRect->setPoint(pl1, pl2, pl3, pl4);
	m_leftMoCircle->setPoint(centerl);

}



void Flipper::updata() {
	Input* input = input->instance();
	//操作逆転
	bool rightKeyDown = input->isKeyDown(KEY_INPUT_RIGHT);
	bool rightKeyUp = input->isKeyUp(KEY_INPUT_RIGHT);
	bool leftKeyDown = input->isKeyDown(KEY_INPUT_LEFT);
	bool leftKeyUp = input->isKeyUp(KEY_INPUT_LEFT);
	if (m_Reverse & 0x1) {
		bool tempD = rightKeyDown;
		bool tempU = rightKeyUp;
		rightKeyDown = leftKeyDown;
		rightKeyUp = leftKeyUp;
		leftKeyDown = tempD;
		leftKeyUp = tempU;
	}
	if (m_Reverse & 0x2) { //左が上下逆か
		leftKeyDown = !leftKeyDown;
		leftKeyUp = !leftKeyDown;
	}
	if (m_Reverse & 0x4) { //右が上下逆か
		rightKeyDown = !rightKeyDown;
		rightKeyUp = !rightKeyDown;
	}



	if (rightKeyDown && m_radRight <= -1.09) {
		if (m_radPowerRight >= 0.0)
			PlaySoundMem(m_SE, DX_PLAYTYPE_BACK);
		m_radRight += 0.2;
		if (m_radPowerRight < 0.0)
			m_radPowerRight = 0.0;
		m_radPowerRight -= 0.1;

		//角度からフリッパーを生成
		double cosR = cos(m_radRight - 1.5707);
		double sinR = sin(m_radRight - 1.5707);
		Vector2D p3 = m_posRight + Vector2D((-5.0 * cosR) - (20 * sinR), (-5.0 * sinR) + (cosR * 20.0));
		Vector2D p2 = m_posRight + Vector2D((-5.0 * cosR) + (20 * sinR), (-5.0 * sinR) - (cosR * 20.0));
		Vector2D center = m_posRight + Vector2D(60 * cos(m_radRight - 1.5707), 60 * sin(m_radRight - 1.5707));
		Vector2D p4 = m_posRight + Vector2D((60.0 * cosR) - (15 * sinR), (60.0 * sinR) + (cosR * 15.0));
		Vector2D p1 = m_posRight + Vector2D((60.0 * cosR) + (15 * sinR), (60.0 * sinR) - (cosR * 15.0));
		m_rightRect->setPoint(p1, p2, p3, p4);
		m_rightMoCircle->setPoint(center);
	}
	else if (rightKeyUp && m_radRight >= -1.91) {
		if (m_radPowerRight <= 0.0)
			PlaySoundMem(m_SE, DX_PLAYTYPE_BACK);
		m_radRight -= 0.2;
		if (m_radPowerRight > 0.0)
			m_radPowerRight = 0.0;
		m_radPowerRight += 0.1;
		//角度からフリッパーを生成
		double cosR = cos(m_radRight - 1.5707);
		double sinR = sin(m_radRight - 1.5707);
		Vector2D p3 = m_posRight + Vector2D((-5.0 * cosR) - (20 * sinR), (-5.0 * sinR) + (cosR * 20.0));
		Vector2D p2 = m_posRight + Vector2D((-5.0 * cosR) + (20 * sinR), (-5.0 * sinR) - (cosR * 20.0));
		Vector2D center = m_posRight + Vector2D(60 * cos(m_radRight - 1.5707), 60 * sin(m_radRight - 1.5707));
		Vector2D p4 = m_posRight + Vector2D((60.0 * cosR) - (15 * sinR), (60.0 * sinR) + (cosR * 15.0));
		Vector2D p1 = m_posRight + Vector2D((60.0 * cosR) + (15 * sinR), (60.0 * sinR) - (cosR * 15.0));
		m_rightRect->setPoint(p1, p2, p3, p4);
		m_rightMoCircle->setPoint(center);

	}
	else {
		m_radPowerRight = 0.0;
	}
	if (leftKeyDown && m_radLeft >= 1.09) {
		if (m_radPowerLeft >= 0.0)
			PlaySoundMem(m_SE, DX_PLAYTYPE_BACK);
		m_radLeft -= 0.2;
		if (m_radPowerLeft < 0.0)
			m_radPowerLeft = 0.0;
		m_radPowerLeft -= 0.1;
		//角度からフリッパーを生成
		double cosL = cos(m_radLeft - 1.5707);
		double sinL = sin(m_radLeft - 1.5707);
		Vector2D pl1 = m_posLeft + Vector2D((-5.0 * cosL) - (20 * sinL), (-5.0 * sinL) + (cosL * 20.0));
		Vector2D pl4 = m_posLeft + Vector2D((-5.0 * cosL) + (20 * sinL), (-5.0 * sinL) - (cosL * 20.0));
		Vector2D centerl = m_posLeft + Vector2D(60 * cos(m_radLeft - 1.5707), 60 * sin(m_radLeft - 1.5707));
		Vector2D pl2 = m_posLeft + Vector2D((60.0 * cosL) - (15 * sinL), (60.0 * sinL) + (cosL * 15.0));
		Vector2D pl3 = m_posLeft + Vector2D((60.0 * cosL) + (15 * sinL), (60.0 * sinL) - (cosL * 15.0));
		m_leftRect->setPoint(pl1, pl2, pl3, pl4);
		m_leftMoCircle->setPoint(centerl);

	}
	else if (leftKeyUp && m_radLeft <= 1.91) {
		if (m_radPowerLeft <= 0.0)
			PlaySoundMem(m_SE, DX_PLAYTYPE_BACK);
		m_radLeft += 0.2;
		if (m_radPowerLeft > 0.0)
			m_radPowerLeft = 0.0;
		m_radPowerLeft += 0.1;
		//角度からフリッパーを生成
		double cosL = cos(m_radLeft - 1.5707);
		double sinL = sin(m_radLeft - 1.5707);
		Vector2D pl1 = m_posLeft + Vector2D((-5.0 * cosL) - (20 * sinL), (-5.0 * sinL) + (cosL * 20.0));
		Vector2D pl4 = m_posLeft + Vector2D((-5.0 * cosL) + (20 * sinL), (-5.0 * sinL) - (cosL * 20.0));
		Vector2D centerl = m_posLeft + Vector2D(60 * cos(m_radLeft - 1.5707), 60 * sin(m_radLeft - 1.5707));
		Vector2D pl2 = m_posLeft + Vector2D((60.0 * cosL) - (15 * sinL), (60.0 * sinL) + (cosL * 15.0));
		Vector2D pl3 = m_posLeft + Vector2D((60.0 * cosL) + (15 * sinL), (60.0 * sinL) - (cosL * 15.0));
		m_leftRect->setPoint(pl1, pl2, pl3, pl4);
		m_leftMoCircle->setPoint(centerl);
	}
	else {
		m_radPowerLeft = 0.0;
	}
	m_leftMoCircle->updataPower(m_radPowerLeft);
	m_leftRect->updataPower(m_radPowerLeft);
	m_rightMoCircle->updataPower(m_radPowerRight);
	m_rightRect->updataPower(m_radPowerRight);
}




void Flipper::draw(){
	//DrawFormatString(50, 300, GetColor(100, 100, 200), "radR: %f, radL: %f, powerR: %f, powerL %f", m_radRight, m_radLeft, m_radPowerRight, m_radPowerLeft);
	//DrawFormatString(50, 300, GetColor(100, 100, 200), "%x", m_Reverse);
	//m_leftCircle->draw();
	//m_rightCircle->draw();
	//m_leftMoCircle->draw();
	//m_rightMoCircle->draw();
	m_rightRect->draw();
	m_leftRect->draw();
	DrawRotaGraph2(190, 745, 5, 8, 1.0, m_radLeft - 1.6, m_graph_flipper, true, FALSE);
	DrawRotaGraph2(316, 745, 55, 8, 1.0, m_radRight + 1.6, m_graph_flipper, true, TRUE);
	//DrawRotaGraph2(m_posLeft.x, m_posLeft.y, 5, 30, 1, m_radLeft-1.5707, m_graph_flipper, 1);
	//DrawRotaGraph2(m_posRight.x, m_posRight.y, 5, 30, 1, m_radRight-1.5707, m_graph_flipper, 1,1);
}

void Flipper::setReverse(char c) {
	m_Reverse = c;
}

FlipperCircle* const Flipper::getCircle(int num) {
	switch (num)
	{
	case 1:
		return m_leftCircle;
		break;
	case 2:
		return m_leftMoCircle;
		break;
	case 3:
		return m_rightMoCircle;
		break;
	default:
		return m_rightCircle;
	}
}
FlipperRect* const Flipper::getRect(int num) {
	if (num == 1)
		return m_leftRect;
	else
		return m_rightRect;
}

//FlipperCircle


FlipperCircle::FlipperCircle(Vector2D center, double rad) : m_pos(center),m_rad(rad),m_power(0.0) {}

void FlipperCircle::draw() {
	DrawCircleAA((float)m_pos.x, (float)m_pos.y, (float)m_rad, 24, GetColor(250, 250, 250), 0, 1.0);
}

void const FlipperCircle::getPoint(Vector2D& p1){
	p1 = m_pos;
}

void FlipperCircle::setPoint(Vector2D p1){
	m_pos = p1;
}

bool FlipperCircle::BallCollide(Vector2D ballPos, Vector2D ballNextPos) {
	return true;
}



double FlipperCircle::pointDiff(Vector2D p1, Vector2D p2) { return 1.0; }
double FlipperCircle::reflectionBall(Vector2D& ballPos, Vector2D& ballVec, double buff) { return 1.0; }

void FlipperCircle::updataPower(double p){
	m_power = p;
}



//FlipperRect

FlipperRect::FlipperRect(Vector2D p1, Vector2D p2, Vector2D p3, Vector2D p4,bool isLeft) : m_point1(p1), m_point2(p2), m_point3(p3), m_point4(p4),m_power(0.0),m_isLeft(isLeft) {
}

FlipperRect::FlipperRect( bool isLeft) :  m_isLeft(isLeft), m_power(0.0) {
}

void FlipperRect::draw() {
	/*
	DrawLineAA(m_point1.x, m_point1.y, m_point2.x, m_point2.y, GetColor(250, 250, 250), 1.0);
	DrawLineAA(m_point3.x, m_point3.y, m_point4.x, m_point4.y, GetColor(250, 250, 250), 1.0);
	DrawLineAA(m_point3.x, m_point3.y, m_point2.x, m_point2.y, GetColor(250, 250, 250), 1.0);
	DrawLineAA(m_point1.x, m_point1.y, m_point4.x, m_point4.y, GetColor(250, 250, 250), 1.0);
	*/
	//DrawString(m_point1.x, m_point1.y, "1", GetColor(200, 200, 200));
	//DrawString(m_point2.x, m_point2.y, "2", GetColor(200, 200, 200));
	//DrawString(m_point3.x, m_point3.y, "3", GetColor(200, 200, 200));
	//DrawString(m_point4.x, m_point4.y, "4", GetColor(200, 200, 200));
}


void const FlipperRect::getPoint(Vector2D& p1, Vector2D& p2, Vector2D& p3, Vector2D& p4){
	p1 = m_point1;
	p2 = m_point2;
	p3 = m_point3;
	p4 = m_point4;
}

void FlipperRect::setPoint(Vector2D p1, Vector2D p2, Vector2D p3, Vector2D p4){
	m_point1 = p1;
	m_point2 = p2;
	m_point3 = p3;
	m_point4 = p4;
}

bool FlipperRect::BallCollide(Vector2D ballPos, Vector2D ballNextPos) {
	bool posIsIn = false;//ballPosが中にいるかどうか
	bool nextPosIsIn = false;//ballNextPosが中にいるかどうか
	
	double a1 = cross(m_point2 - m_point1, ballPos - m_point1);
	double a2 = cross(m_point3 - m_point2, ballPos - m_point2);
	double a3 = cross(m_point4 - m_point3, ballPos - m_point3);
	double a4 = cross(m_point1 - m_point4, ballPos - m_point4);
	double b1 = cross(m_point2 - m_point1, ballNextPos - m_point1);
	double b2 = cross(m_point3 - m_point2, ballNextPos - m_point2);
	double b3 = cross(m_point4 - m_point3, ballNextPos - m_point3);
	double b4 = cross(m_point1 - m_point4, ballNextPos - m_point4);

	
	if (a1 < 0 && a2 < 0 && a3 < 0 && a4 < 0)
		posIsIn = true;
	if (b1 < 0 && b2 < 0 && b3 < 0 && b4 < 0)
		nextPosIsIn = true;

	if (posIsIn == true || nextPosIsIn == true) {
		return true;
	}
	//フリッパー丸ごと通り越した場合
	if (a1 * b1 < 0.0) {
		if (cross(ballNextPos - ballPos, m_point1 - ballPos) * cross(ballNextPos - ballPos, m_point2 - ballPos) < 0.0) {
			return true;
		}
	}
	else if (a3 * b3 < 0.0) {
		if (cross(ballNextPos - ballPos, m_point3 - ballPos) * cross(ballNextPos - ballPos, m_point4 - ballPos) < 0.0) {
			return true;
			
		}
	}
	return false;
}

double FlipperRect::pointDiff(Vector2D ballPos, Vector2D ballNextPos) {
	if ((0 < m_power && m_power > 0.001) || (m_power < 0 && m_power > -0.001)) {//誤差対策
		return 0.0;//フリッパーが動いてる場合は優先的に処理
	}
	else {
		bool posIsIn = false;//ballPosが中にいるかどうか
		bool nextPosIsIn = false;//ballNextPosが中にいるかどうか
		double a1 = cross(m_point2 - m_point1, ballPos - m_point1);
		double a2 = cross(m_point3 - m_point2, ballPos - m_point2);
		double a3 = cross(m_point4 - m_point3, ballPos - m_point3);
		double a4 = cross(m_point1 - m_point4, ballPos - m_point4);
		double b1 = cross(m_point2 - m_point1, ballNextPos - m_point1);
		double b2 = cross(m_point3 - m_point2, ballNextPos - m_point2);
		double b3 = cross(m_point4 - m_point3, ballNextPos - m_point3);
		double b4 = cross(m_point1 - m_point4, ballNextPos - m_point4);
		Vector2D pVec = ballNextPos - ballPos;
		if (a1 < 0 && a2 < 0 && a3 < 0 && a4 < 0)
			posIsIn = true;
		if (b1 < 0 && b2 < 0 && b3 < 0 && b4 < 0)
			nextPosIsIn = true;
		if (posIsIn == true && nextPosIsIn == true) {
			return 0.0;
		}
		else if (posIsIn == false && nextPosIsIn == true) {
			Vector2D wallVec,pointC;
			if ((cross(m_point2 - m_point1, ballPos - m_point1) * cross(m_point2 - m_point1, ballNextPos - m_point1)) < 0.0) {
				wallVec = m_point2 - m_point1;
				pointC = m_point1;
			}
			else if ((cross(m_point3 - m_point2, ballPos - m_point2) * cross(m_point3 - m_point2, ballNextPos - m_point2)) < 0.0) {
				wallVec = m_point3 - m_point2;
				pointC = m_point2;
			}
			else if ((cross(m_point4 - m_point3, ballPos - m_point3) * cross(m_point4 - m_point3, ballNextPos - m_point3)) < 0.0) {
				wallVec = m_point4 - m_point3;
				pointC = m_point3;
			}
			else {
				wallVec = m_point1 - m_point4;
				pointC = m_point4;
			}
			double b = cross(ballPos - pointC, ballNextPos - pointC) / cross(wallVec, pVec);
			double crossX = pointC.x + b * (wallVec).x;//衝突位置を特定
			double crossY = pointC.y + b * (wallVec).y;
			double diff = (crossX - ballPos.x) * (crossX - ballPos.x) + (crossY - ballPos.y) * (crossY - ballPos.y);
			return diff;
		}
		else {
			Vector2D wallVecP[] = { m_point2 - m_point1,m_point3 - m_point2,m_point4 - m_point3,m_point1 - m_point4 };
			Vector2D pointP[] = { m_point1,m_point2,m_point3,m_point4 };
			double b, crossX, crossY, diff = 0.0;
			for (int j = 0; j < 4; j++) {
				if ((cross(wallVecP[j], ballPos - pointP[j]) * cross(wallVecP[j], ballNextPos - pointP[j])) < 0.0)
				{
					b = cross(ballPos - pointP[j], ballNextPos - pointP[j]) / cross(wallVecP[j], pVec);
					crossX = pointP[j].x + b * (wallVecP[j]).x;//衝突位置を特定
					crossY = pointP[j].y + b * (wallVecP[j]).y;
					double tDiff = (crossX - ballPos.x) * (crossX - ballPos.x) + (crossY - ballPos.y) * (crossY - ballPos.y);
					if (tDiff > diff) {
						diff = tDiff;
					}

				}
			}
			return diff;
		}

	}
	return 10.0;
}





double FlipperRect::reflectionBall(Vector2D& ballPos, Vector2D& ballVec, double buff) { 
	Vector2D ballNextPos = ballPos + ballVec * buff;
	bool posIsIn = false;//ballPosが中にいるかどうか
	bool nextPosIsIn = false;//ballNextPosが中にいるかどうか
	double a1 = cross(m_point2 - m_point1, ballPos - m_point1);
	double a2 = cross(m_point3 - m_point2, ballPos - m_point2);
	double a3 = cross(m_point4 - m_point3, ballPos - m_point3);
	double a4 = cross(m_point1 - m_point4, ballPos - m_point4);
	double b1 = cross(m_point2 - m_point1, ballNextPos - m_point1);
	double b2 = cross(m_point3 - m_point2, ballNextPos - m_point2);
	double b3 = cross(m_point4 - m_point3, ballNextPos - m_point3);
	double b4 = cross(m_point1 - m_point4, ballNextPos - m_point4);
	if (a1 < 0 && a2 < 0 && a3 < 0 && a4< 0)
		posIsIn = true;
	if (b1 < 0 && b2 < 0 && b3 < 0&& b4 < 0)
		nextPosIsIn = true;
	if (m_power != 0) { //フリッパーが動いてるとき
		if (posIsIn == true && nextPosIsIn == true) {
			if (m_isLeft == true) {
				if (m_power < 0) {
					Vector2D wallVec = m_point3 - m_point4;
					Vector2D fakePos = ballPos + Vector2D(0, -100);
					double b = cross(ballPos - m_point3, fakePos - m_point3) / cross(wallVec, Vector2D(0, -100));
					double crossX = m_point3.x + b * (wallVec).x;//衝突位置を特定
					double crossY = m_point3.y + b * (wallVec).y;
					Vector2D crossPoint(crossX, crossY);
					Vector2D FvecR = crossPoint - m_point4;
					Vector2D Fvec(FvecR.y, -FvecR.x);
					Fvec *= 0.7 * (1 + m_power * 2);
					ballVec = Fvec;
					ballPos = crossPoint + (ballVec * 0.0001);
				}
				else {
					Vector2D wallVec = m_point1 - m_point2;
					Vector2D fakePos = ballPos + Vector2D(0, 100);
					double b = cross(ballPos - m_point1, fakePos - m_point1) / cross(wallVec, Vector2D(0, 100));
					double crossX = m_point1.x + b * (wallVec).x;//衝突位置を特定
					double crossY = m_point1.y + b * (wallVec).y;
					Vector2D crossPoint(crossX, crossY);
					Vector2D FvecR = crossPoint - m_point1;
					Vector2D Fvec(-FvecR.y, FvecR.x);
					Fvec *= 0.1 * (1 + m_power * 2);
					ballVec = Fvec;
					ballPos = crossPoint + (ballVec * 0.0001);

				}
			}
			else {
				if (m_power < 0) {
					Vector2D wallVec = m_point3 - m_point4;
					Vector2D fakePos = ballPos + Vector2D(0, -100);
					double b = cross(ballPos - m_point3, fakePos - m_point3) / cross(wallVec, Vector2D(0, -100));
					double crossX = m_point3.x + b * (wallVec).x;//衝突位置を特定
					double crossY = m_point3.y + b * (wallVec).y;
					Vector2D crossPoint(crossX, crossY);
					Vector2D FvecR = crossPoint - m_point3;
					Vector2D Fvec(-FvecR.y, FvecR.x);
					Fvec *= 0.7 * (1 + m_power * 2);
					ballVec = Fvec;
					ballPos = crossPoint + (ballVec * 0.0001);

				}
				else {
					Vector2D wallVec = m_point1 - m_point2;
					Vector2D fakePos = ballPos + Vector2D(0, 100);
					double b = cross(ballPos - m_point1, fakePos - m_point1) / cross(wallVec, Vector2D(0, 100));
					double crossX = m_point1.x + b * (wallVec).x;//衝突位置を特定
					double crossY = m_point1.y + b * (wallVec).y;
					Vector2D crossPoint(crossX, crossY);
					Vector2D FvecR = crossPoint - m_point2;
					Vector2D Fvec(FvecR.y, -FvecR.x);
					Fvec *= 0.1 * (1 + m_power * 2);
					ballVec = Fvec;
					ballPos = crossPoint + (ballVec * 0.0001);
				}
			}
			if (ballVec.lengthSq() > 400)
				ballVec = ballVec.normalizeVec() * 20.0;
		}
		else if (posIsIn == true && nextPosIsIn == false) {
		}
		else if (posIsIn == false && nextPosIsIn == true) {
			double crossX, crossY;
			Vector2D wallVec;
			if ((cross(m_point2 - m_point1, ballPos - m_point1) * cross(m_point2 - m_point1, ballNextPos - m_point1)) < 0.0) {
				wallVec = m_point2 - m_point1;
				Vector2D pVec = ballNextPos - ballPos;
				double b = cross(ballPos - m_point1, ballNextPos - m_point1) / cross(wallVec, pVec);
				crossX = m_point1.x + b * (wallVec).x;//衝突位置を特定
				crossY = m_point1.y + b * (wallVec).y;
				Vector2D crossPoint(crossX, crossY);
				if (m_isLeft == true) {
					Vector2D FvecR = crossPoint - m_point1;
					Vector2D Fvec(-FvecR.y, FvecR.x);
					Fvec *= 0.7 * (1 + m_power * 2);
					ballVec = Fvec;
					ballPos = crossPoint + (ballVec * 0.01);
				}
				else {
					Vector2D FvecR = crossPoint - m_point2;
					Vector2D Fvec(FvecR.y, -FvecR.x);
					Fvec *= 0.7 * (1 + m_power * 2);
					ballVec = Fvec;
					ballPos = crossPoint + (ballVec * 0.0001);
				}

			}
			else if ((cross(m_point3 - m_point2, ballPos - m_point2) * cross(m_point3 - m_point2, ballNextPos - m_point2)) < 0.0) {
				wallVec = m_point3 - m_point2;
				Vector2D pVec = ballNextPos - ballPos;
				double b = cross(ballPos - m_point2, ballNextPos - m_point2) / cross(wallVec, pVec);
				crossX = m_point2.x + b * (wallVec).x;//衝突位置を特定
				crossY = m_point2.y + b * (wallVec).y;
				Vector2D crossP(crossX, crossY);
				Vector2D newVec = crossP - ballPos;
				Vector2D normalVec(-wallVec.y, wallVec.x);
				normalVec.normalize();
				normalVec *= dot(newVec.inverse(), normalVec);
				double power = ballVec.length();
				ballVec = normalVec + normalVec + newVec;
				ballVec = ballVec.normalizeVec() * power * 0.7;
				ballPos = crossP + (ballVec * 0.000001);
			}
			else if ((cross(m_point4 - m_point3, ballPos - m_point3) * cross(m_point4 - m_point3, ballNextPos - m_point3)) < 0.0) {
				wallVec = m_point4 - m_point3;
				Vector2D pVec = ballNextPos - ballPos;
				double b = cross(ballPos - m_point3, ballNextPos - m_point3) / cross(wallVec, pVec);
				crossX = m_point3.x + b * (wallVec).x;//衝突位置を特定
				crossY = m_point3.y + b * (wallVec).y;
				Vector2D crossPoint(crossX, crossY);
				if (m_isLeft == true) {
					Vector2D FvecR = crossPoint - m_point4;
					Vector2D Fvec(FvecR.y, -FvecR.x);
					Fvec *= 0.7 * (1 + m_power * 2);
					ballVec = Fvec;
					ballPos = crossPoint + (ballVec * 0.0001);
				}
				else {
					Vector2D FvecR = crossPoint - m_point3;
					Vector2D Fvec(-FvecR.y, FvecR.x);
					Fvec *= 0.7 * (1 + m_power * 2);
					ballVec = Fvec;
					ballPos = crossPoint + (ballVec * 0.0001);
				}
			}
			else {
				wallVec = m_point1 - m_point4;
				Vector2D pVec = ballNextPos - ballPos;
				double b = cross(ballPos - m_point4, ballNextPos - m_point4) / cross(wallVec, pVec);
				crossX = m_point4.x + b * (wallVec).x;//衝突位置を特定
				crossY = m_point4.y + b * (wallVec).y;
				Vector2D crossP(crossX, crossY);
				Vector2D newVec = crossP - ballPos;
				Vector2D normalVec(-wallVec.y, wallVec.x);
				normalVec.normalize();
				normalVec *= dot(newVec.inverse(), normalVec);
				double power = ballVec.length();
				ballVec = normalVec + normalVec + newVec;
				ballVec = ballVec.normalizeVec() * power * 0.7;
				ballPos = crossP + (ballVec * 0.000001);
			}
			//	m_vec *= -1;
			return 0.0;
		}
		else { 
			Vector2D wallVecP[] = { m_point2 - m_point1,m_point3 - m_point2,m_point4 - m_point3,m_point1 - m_point4 };
			Vector2D pointP[] = { m_point1,m_point2,m_point3,m_point4 };
			double crossX, crossY, diff = 500000.0;
			int cj;
			for (int j = 0; j < 4; j++) {
				if ((cross(wallVecP[j], ballPos - pointP[j]) * cross(wallVecP[j], ballNextPos - pointP[j])) < 0.0)
				{
					double b = cross(ballPos - pointP[j], ballNextPos - pointP[j]) / cross(wallVecP[j], ballVec * buff);
					double TCrossX = pointP[j].x + b * (wallVecP[j]).x;//衝突位置を特定
					double TCrossY = pointP[j].y + b * (wallVecP[j]).y;
					double tDiff = (TCrossX - ballPos.x) * (TCrossX - ballPos.x) + (TCrossY - ballPos.y) * (TCrossY - ballPos.y);
					if (tDiff < diff) {
						diff = tDiff;
						cj = j;
						crossX = TCrossX;
						crossY = TCrossY;
					}

				}
			}

			if (diff == 500000.0)
				return 0.0;
			Vector2D crossP(crossX, crossY);
			Vector2D newVec = crossP - ballPos;
			Vector2D normalVec(-wallVecP[cj].y, wallVecP[cj].x);
			normalVec.normalize();
			normalVec *= dot(newVec.inverse(), normalVec);
			double power = ballVec.length();
			ballVec = normalVec + normalVec + newVec;
			ballVec = ballVec.normalizeVec() * power * 0.7;
			ballPos = crossP + (ballVec * 0.000001);
			return 0.0;
		}
		return 0.0;
		
	}
	//フリッパーが動いてないとき
	else {
		if (posIsIn == false && nextPosIsIn == true) {
			Vector2D wallVec, pointC;
			if ((cross(m_point2 - m_point1, ballPos - m_point1) * cross(m_point2 - m_point1, ballNextPos - m_point1)) < 0.0) {
				wallVec = m_point2 - m_point1;
				pointC = m_point1;
			}
			else if ((cross(m_point3 - m_point2, ballPos - m_point2) * cross(m_point3 - m_point2, ballNextPos - m_point2)) < 0.0) {
				wallVec = m_point3 - m_point2;
				pointC = m_point2;
			}
			else if ((cross(m_point4 - m_point3, ballPos - m_point3) * cross(m_point4 - m_point3, ballNextPos - m_point3)) < 0.0) {
				wallVec = m_point4 - m_point3;
				pointC = m_point3;
			}
			else {
				wallVec = m_point1 - m_point4;
				pointC = m_point4;
			}
			double b = cross(ballPos - pointC, ballNextPos - pointC) / cross(wallVec, ballVec * buff);
			double crossX = pointC.x + b * (wallVec).x;//衝突位置を特定
			double crossY = pointC.y + b * (wallVec).y;
			Vector2D crossPoint(crossX, crossY);
			Vector2D newVec = crossPoint - ballPos;
			Vector2D normalVec(-wallVec.y, wallVec.x);
			normalVec.normalize();
			normalVec *= dot(newVec.inverse(), normalVec);
			double power = ballVec.length();
			ballVec = normalVec + normalVec + newVec;
			ballVec = ballVec.normalizeVec() * power * 0.7;
			ballPos = crossPoint + (ballVec * 0.000001);
			//	m_vec *= -1;
			return 0.0;
		}
		else if (posIsIn == false && nextPosIsIn == false) {//ボールがフリッパーを通り過ぎたとき
			Vector2D wallVecP[] = { m_point2 - m_point1,m_point3 - m_point2,m_point4 - m_point3,m_point1 - m_point4 };
			Vector2D pointP[] = { m_point1,m_point2,m_point3,m_point4 };
			double crossX, crossY, diff = 500000.0;
			int cj;
			for (int j = 0; j < 4; j++) {
				if ((cross(wallVecP[j], ballPos - pointP[j]) * cross(wallVecP[j], ballNextPos - pointP[j])) < 0.0)
				{
					double b = cross(ballPos - pointP[j], ballNextPos - pointP[j]) / cross(wallVecP[j], ballVec * buff);
					double TCrossX = pointP[j].x + b * (wallVecP[j]).x;//衝突位置を特定
					double TCrossY = pointP[j].y + b * (wallVecP[j]).y;
					double tDiff = (TCrossX - ballPos.x) * (TCrossX - ballPos.x) + (TCrossY - ballPos.y) * (TCrossY - ballPos.y);
					if (tDiff < diff) {
						diff = tDiff;
						cj = j;
						crossX = TCrossX;
						crossY = TCrossY;
					}

				}
			}
			if (diff == 500000.0)
				return 0.0;
			Vector2D crossP(crossX, crossY);
			Vector2D newVec = crossP - ballPos;
			Vector2D normalVec(-wallVecP[cj].y, wallVecP[cj].x);
			normalVec.normalize();
			normalVec *= dot(newVec.inverse(), normalVec);
			double power = ballVec.length();
			ballVec = normalVec + normalVec + newVec;
			ballVec = ballVec.normalizeVec() * power * 0.7;
			ballPos = crossP + (ballVec * 0.000001);
			return 0.0;
		}
		else if (posIsIn == true && nextPosIsIn == false){
			return 0.0;
		}
		else {
			/*
			Vector2D wallVec, pointC;

			Vector2D fakePos = ballPos - ballVec * 5.0;
			if ((cross(m_point2 - m_point1, fakePos - m_point1) * cross(m_point2 - m_point1, ballNextPos - m_point1)) < 0.0) {
				wallVec = m_point2 - m_point1;
				pointC = m_point1;
			}
			else if ((cross(m_point3 - m_point2, fakePos - m_point2) * cross(m_point3 - m_point2, ballNextPos - m_point2)) < 0.0) {
				wallVec = m_point3 - m_point2;
				pointC = m_point2;
			}
			else if ((cross(m_point4 - m_point3, fakePos - m_point3) * cross(m_point4 - m_point3, ballNextPos - m_point3)) < 0.0) {
				wallVec = m_point4 - m_point3;
				pointC = m_point3;
			}
			else {
				wallVec = m_point1 - m_point4;
				pointC = m_point4;
			}


			double b = cross(fakePos - pointC, ballNextPos - pointC) / cross(wallVec, ballVec);
			double crossX = pointC.x + b * (wallVec).x;//衝突位置を特定
			double crossY = pointC.y + b * (wallVec).y;
			Vector2D crossPoint(crossX, crossY);
			Vector2D normalVec(-wallVec.y, wallVec.x);
			normalVec.normalize();
			normalVec *= dot(ballVec.inverse(), normalVec);
			double power = ballVec.length();
			ballVec = normalVec + normalVec + ballVec;
			ballVec = ballVec.normalizeVec() * power * 0.7;
			ballPos = crossPoint + (ballVec * 0.000001);
			*/
			return 0.0;
		}
	}

}

void FlipperRect::updataPower(double p){
	m_power = p;
}

int Flipper::m_SE = 0;