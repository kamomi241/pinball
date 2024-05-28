#include "DxLib.h"
#include <time.h>

class Effect {
public:
	Effect();
	void Hari(int ex,int ey);
	void Sord(int, int);
	void God(int, int);
	void Steki(int, int);
	void Book(int, int);
	void Magic(int, int);
	void Wood(int, int);
	void Aosan(int, int);
	void Cannon(int,int);
	void Akasan(int, int);
	void Choice(int ex, int ey, int kind);
	void test();
private:
	bool start;
	int starttime;
	int nowtime;
	int cannon;
	int cannonmove;
	int wood;
	int aosan;
	int steki;
	int hari;
};