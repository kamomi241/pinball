#include "DxLib.h"
#include "Input.h"

class Startmenu {
public:
	Startmenu();
	bool Start();
	bool tutorial();
private:
	int image_menu;
	bool start;
	int move;
	int image1;		//�`���[�g���A���摜
	int image2;
	bool tutorialf;
	int page;
};