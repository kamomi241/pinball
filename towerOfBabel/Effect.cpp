#include "Effect.h"

Effect::Effect() {
	start = true;
	cannon = LoadGraph("effect\\cannon.png");
	wood = LoadGraph("effect\\wood.png");
	hari = LoadGraph("effect\\hari.png");
	aosan = LoadGraph("effect\\aosan.png");
	steki = LoadGraph("effect\\stekki.png");
	nowtime = 0;
	starttime = 0; 
	cannonmove = 0;
}

void Effect::Choice(int ex, int ey, int kind) {
	switch (kind)
	{
	case 0:
		Hari(ex, ey);
		break;
	case 1:
	case 2:
		Cannon(ex, ey);
		break;
	case 3:
	case 4:
	case 5:
		Steki(ex, ey);
		break;
	case 6:
	case 8:
		Wood(ex, ey);
		break;
	case 7:
	case 9:
		Aosan(ex, ey);
		break;
	default:
		break;
	}
}
void Effect::Cannon(int ex, int ey) {
	if (start == true) {
		start = false;
		starttime = clock();
	}
	
	if (800 <= clock() - starttime)
		start = true;
	if (750 <= clock() - starttime)
		DrawRectGraph(ex + 20, ey + 70, 1700, 40, 100, 100, cannon, TRUE, FALSE);
	else if (700 <= clock() - starttime)
		DrawRectGraph(ex + 20, ey + 70, 1500, 40, 100, 100, cannon, TRUE, FALSE);
	else if(650 <= clock() - starttime)
		DrawRectGraph(ex + 20, ey + 70, 1300, 40, 100, 100, cannon, TRUE, FALSE);
	else if(600 <= clock() - starttime)
		DrawRectGraph(ex + 0, ey + 50, 1110, 50, 100, 100, cannon, TRUE, FALSE);
	else if(550 <= clock() - starttime)
		DrawRectGraph(ex, ey + 50, 950, 40, 90, 100, cannon, TRUE, FALSE);
	else if(500 <= clock() - starttime)
		DrawRectGraph(ex, ey + 50, 750, 30, 120, 120, cannon, TRUE, FALSE);
	else if(450 <= clock() - starttime) 
		DrawRectGraph(ex, ey + 50, 540, 30, 155, 120, cannon, TRUE, FALSE);
	else if(400 <= clock() - starttime) 
		DrawRectGraph(ex, ey + 50, 380, 30, 130, 120, cannon, TRUE, FALSE);
	else if(350 <= clock() - starttime)
		DrawRectGraph(ex + 20, ey + 70, 215, 40, 110, 110, cannon, TRUE, FALSE);	
	else if(  0 <= clock() - starttime) 
		DrawRectGraph(ex + 20, ey + 50, 50, 50, 100, 100, cannon, TRUE, FALSE);
}

void Effect::Wood(int ex, int ey) {
	if (start == true) {
		start = false;
		starttime = clock();
	}
	if (550 <= clock() - starttime)
		start = true;
	else if (500 <= clock() - starttime)
	DrawRectGraph(ex ,ey + 50, 800, 0, 100, 300, wood, TRUE, FALSE);
	else if (450 <= clock() - starttime)
	DrawRectGraph(ex ,ey + 50, 600, 0, 100, 300, wood, TRUE, FALSE);
	else if (400 <= clock() - starttime)
	DrawRectGraph(ex ,ey + 50, 400, 0, 100, 300, wood, TRUE, FALSE);
	else if (350 <= clock() - starttime)
	DrawRectGraph(ex ,ey + 50, 235, 0, 100, 300, wood, TRUE, FALSE);
	else if (  0 <= clock() - starttime)
	DrawRectGraph(ex ,ey + 50,  30, 0, 100, 300, wood, TRUE, FALSE);
}

void Effect::Hari(int ex, int ey) {
	if (start == true) {
		start = false;
		starttime = clock();
	}
	if (750 <= clock() - starttime)
		start = true;
	else if (700 <= clock() - starttime)
		DrawRectGraph(ex, ey + 50, 270, 0, 100, 300, hari, TRUE, FALSE);
	else if (650 <= clock() - starttime)
		DrawRectGraph(ex, ey + 50, 240, 0, 100, 300, hari, TRUE, FALSE);
	else if (600 <= clock() - starttime)
		DrawRectGraph(ex, ey + 50, 210, 0, 100, 300, hari, TRUE, FALSE);
	else if (550 <= clock() - starttime)
		DrawRectGraph(ex, ey + 50, 150, 0, 100, 300, hari, TRUE, FALSE);
	else if (500 <= clock() - starttime)
		DrawRectGraph(ex, ey + 50, 120, 0, 100, 200, hari, TRUE, FALSE);
	else if (450 <= clock() - starttime)
		DrawRectGraph(ex, ey + 50, 90, 0, 100, 200, hari, TRUE, FALSE);
	else if (400 <= clock() - starttime)
		DrawRectGraph(ex, ey + 50, 60, 0, 100, 200, hari, TRUE, FALSE);
	else if (350 <= clock() - starttime)
		DrawRectGraph(ex, ey + 50, 30, 0, 100, 200, hari, TRUE, FALSE);
	else if (  0 <= clock() - starttime)
		DrawRectGraph(ex, ey + 50, 0, 0, 100, 200, hari, TRUE, FALSE);
}
void Effect::Aosan(int ex, int ey) {
	if (start == true) {
		start = false;
		starttime = clock();
	}
	if (900 <= clock() - starttime)
		start = true;
	else if (850 <= clock() - starttime)
		DrawRectGraph(0, 100, 50, 600, 100, 200, aosan, TRUE, FALSE);
	else if (800 <= clock() - starttime)
		DrawRectGraph(50, 100, 200, 600, 150, 200, aosan, TRUE, FALSE);
	else if (750 <= clock() - starttime)
		DrawRectGraph(150, 100, 400, 600, 150, 200, aosan, TRUE, FALSE);
	else if (700 <= clock() - starttime)
		DrawRectGraph(250, 100, 600, 600, 150, 200, aosan, TRUE, FALSE);
	else if (660 <= clock() - starttime)
		DrawRectGraph(350, 100, 50, 780, 150, 200, aosan, TRUE, FALSE);
	else if (600 <= clock() - starttime)
		DrawRectGraph(400, 100, 200, 780, 150, 200, aosan, TRUE, FALSE);
	else if (550 <= clock() - starttime)
		DrawRectGraph(500, 100, 400, 780, 150, 200, aosan, TRUE, FALSE);
	else if (500 <= clock() - starttime)
		DrawRectGraph(0, 200, 600, 780, 150, 200, aosan, TRUE, FALSE);
	else if (450 <= clock() - starttime)
		DrawRectGraph(100, 200, 50, 960, 150, 200, aosan, TRUE, FALSE);
	else if (400 <= clock() - starttime)
		DrawRectGraph(200, 200, 200, 960, 150, 200, aosan, TRUE, FALSE);
	else if (350 <= clock() - starttime)
		DrawRectGraph(300, 200, 400, 960, 150, 200, aosan, TRUE, FALSE);
	else if (0 <= clock() - starttime) 
		DrawRectGraph(400, 200, 600, 960, 150, 200, aosan, TRUE, FALSE);
}

void Effect::Steki(int ex, int ey) {
	if (start == true) {
		start = false;
		starttime = clock();
	}

	if (800 <= clock() - starttime)
		start = true;
	if (750 <= clock() - starttime)
		DrawRectGraph(ex + 20, ey + 70, 1700, 40, 100, 100, steki, TRUE, FALSE);
	else if (700 <= clock() - starttime)
		DrawRectGraph(ex + 20, ey + 70, 1500, 40, 100, 100, steki, TRUE, FALSE);
	else if (650 <= clock() - starttime)
		DrawRectGraph(ex + 20, ey + 70, 1300, 40, 100, 100, steki, TRUE, FALSE);
	else if (600 <= clock() - starttime)
		DrawRectGraph(ex + 0, ey + 50, 1110, 50, 100, 100, steki, TRUE, FALSE);
	else if (550 <= clock() - starttime)
		DrawRectGraph(ex, ey + 50, 950, 40, 90, 100, steki, TRUE, FALSE);
	else if (500 <= clock() - starttime)
		DrawRectGraph(ex, ey + 50, 750, 30, 120, 120, steki, TRUE, FALSE);
	else if (450 <= clock() - starttime)
		DrawRectGraph(ex, ey + 50, 540, 30, 155, 120, steki, TRUE, FALSE);
	else if (400 <= clock() - starttime)
		DrawRectGraph(ex, ey + 50, 380, 30, 130, 120, steki, TRUE, FALSE);
	else if (350 <= clock() - starttime)
		DrawRectGraph(ex + 20, ey + 70, 215, 40, 110, 110, steki, TRUE, FALSE);
	else if (0 <= clock() - starttime)
		DrawRectGraph(ex + 20, ey + 50, 50, 50, 100, 100, steki, TRUE, FALSE);
}

void Effect::test() {
	DrawRectGraph(  0, 100,  50, 600, 100, 200, steki, TRUE, FALSE);
	DrawRectGraph( 50, 100, 200, 600, 150, 200, steki, TRUE, FALSE);
	DrawRectGraph(150, 100, 400, 600, 150, 200, steki, TRUE, FALSE);
	DrawRectGraph(250, 100, 600, 600, 150, 200, steki, TRUE, FALSE);
	DrawRectGraph(350, 100,  50, 780, 150, 200, steki, TRUE, FALSE);
	DrawRectGraph(400, 100, 200, 780, 150, 200, steki, TRUE, FALSE);
	DrawRectGraph(500, 100, 400, 780, 150, 200, steki, TRUE, FALSE);
	DrawRectGraph(  0, 200, 600, 780, 150, 200, steki, TRUE, FALSE);
	DrawRectGraph(100, 200,  50, 960, 150, 200, steki, TRUE, FALSE);
	DrawRectGraph(200, 200, 200, 960, 150, 200, steki, TRUE, FALSE);
	DrawRectGraph(300, 200, 400, 960, 150, 200, steki, TRUE, FALSE);
	DrawRectGraph(400, 200, 600, 960, 150, 200, steki, TRUE, FALSE);
}