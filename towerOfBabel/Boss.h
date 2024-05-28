#include "DxLib.h"
#include "Input.h"
#include "Effect.h"
#include <time.h>

class Boss {
public:
	Boss();
	void draw(int*);	//�摜�\��
	bool update(int* time, int* stock, int hit, int* score, int*life,int*bossmove);	//���񂾂�flse
	void hp(int* stock,int hit,int* score,int*,int*);
	void start(int);
	void move(int,int*,int*);
	int* getkillcount();
private:
	int image_boss[5];			//�{�X�摜
	int movie_cameboss[5];
	int sound_gimick[12];
	int boss_type[5][2] = { { 300,0 }, { 300,0 }, { 500,200 }, { 1000,600 }, { 1500,1500 }, };//�̗�,�V�[���h
	int muki[3];
	int mukicount;
	int nowhp;
	int killcount;					//�{�X�̎��
	int x, y;						//�{�X�̓���
	int shield;	
	bool startmove;					//�{�X��J�n��1�x�Ă�
	clock_t starttime;
	clock_t timecount;
	int time_m;
	int time_s;
	int gimicktype[10] = { 0, 0, 0, 1, 1, 1, 0, 1, 0, 1 };
	int gimickatack[10] = { 10,50,100,10,30,50,20,20,30,30 };
	int damage;
	int type;
	bool mukif;
	Effect* effect;
	int effects;
	int effecttime[10] = { 750,800,800,800,800,800,550,550,800,800 };
	int scorepoint[5] = { 180, 210, 300, 480, 600 };
	int effectstop;
	int ey, ex;
	int dief;
	int efecthit;
	bool moviestart;
	int dietime;
	int randatack;
	int beforlife;
};