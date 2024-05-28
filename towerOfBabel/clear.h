#include "DxLib.h"
#include "Input.h"
#include <fstream>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

class Clear {
public:
	Clear();
	bool Score(int* score, int ball);
	int Xor(int, int);
private:
	int image_clear;
	bool highscore;
	int ranctest[6][24];
	int rancin[6][24];
	int ranc[5];			//表示するスコアを入れる
	int rancs;				//分割されていないスコアを入れる
	int testranc[5];
	int i;
	bool first;
	int bgm;
	bool falsify;
	int salt[6][24] = {
	{ 1,0,0,1,1,0,0,0,1,0,0,1,0,1,1,0,0,1,1,1,0,1,1,0 },
	{ 0,1,0,0,1,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,1,0,0,0 },
	{ 0,1,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,1,0,0,0,0,1,0 },
	{ 1,0,0,1,1,0,0,0,1,0,1,1,0,0,1,1,0,1,0,1,1,0,0,1 },
	{ 0,0,1,0,1,1,1,0,0,1,0,1,0,1,1,0,0,0,0,0,1,1,1,0 },
	{ 1,1,1,0,1,0,0,0,1,0,1,1,0,1,0,1,0,1,1,1,0,1,0,1 } };
};