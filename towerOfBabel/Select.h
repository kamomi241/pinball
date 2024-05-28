#include "DxLib.h"
#include "Input.h"
#include <time.h>
#include <cstdlib>

class Select {
public:
	Select();
	void start(int);
	bool make(int, int time, int* stock);
	void button(int, int, int, int, int);
	void button_image(int, int, int, int, int, int);
	void inventory(int, int, int, int, int, int, int*);
	void gimick_detail(int items, int x1, int y1, int q);
	int gimmick[13];
private:
	int movie_dieboss[4];
	int make_image;
	int bgm;
	int inventory_menu;		//押された設置可能場所の確認
	int choice_image;
	int waku_image;
	int okbutton;
	int inventory_count[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };	//所持しているギミック
	bool startbool;
	int gimmickcount;
	int max, min;
	bool over;
	int chancel;
	int detail[10] = { 10,50,100,10,30,50,20,20,30,30 };
	int printgimmic[12] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	char gimmictipe[10][5] = {"物理","物理","物理","魔法", "魔法","魔法", "物理","魔法", "物理","魔法"};
};