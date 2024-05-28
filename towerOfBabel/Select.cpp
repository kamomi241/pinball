#include "Select.h"

Select::Select() {
	make_image = LoadGraph("texture\\select.png");
	choice_image = LoadGraph("texture\\choice.png");
	okbutton = LoadGraph("texture\\selectok.png");
	gimmick[0] = LoadGraph("texture\\hari.png");
	gimmick[1] = LoadGraph("texture\\ken.png");
	gimmick[2] = LoadGraph("texture\\kamiken.png");
	gimmick[3] = LoadGraph("texture\\steki.png");
	gimmick[4] = LoadGraph("texture\\hon.png");
	gimmick[5] = LoadGraph("texture\\tue.png");
	gimmick[6] = LoadGraph("texture\\kisan.png");
	gimmick[7] = LoadGraph("texture\\aosan.png");
	gimmick[8] = LoadGraph("texture\\san.png");
	gimmick[9] = LoadGraph("texture\\akasan.png");
	gimmick[10] = LoadGraph("texture\\panel.png");
	gimmick[11] = LoadGraph("texture\\panel2.png");
	chancel = LoadGraph("texture\\chancel.png");
	movie_dieboss[0] = LoadGraph("texture\\dieslime.mp4");
	movie_dieboss[1] = LoadGraph("texture\\diefox.mp4");
	movie_dieboss[2] = LoadGraph("texture\\diedog.mp4");
	movie_dieboss[3] = LoadGraph("texture\\diedie.mp4");
	bgm = LoadSoundMem("texture\\select.mp3");
	inventory_menu = -1;
	startbool = true;
	gimmickcount = 0;
	srand((int)time(NULL));
	max = 0;
	min = 0;
	over = false;
}

bool Select::make(int killcount, int time, int* stock) {
	if (startbool == true)
		start(killcount);
	DrawExtendGraph(0, 0, 650, 200, movie_dieboss[killcount - 1], FALSE);
	DrawGraph(0, 200, make_image, TRUE);
	DrawBox(0, 3, 80, 28, GetColor(40, 40, 40), TRUE);
	//DrawFormatString(580, 210, GetColor(255, 255, 255), "%02d:%02d\n", time / 60, time % 60);
	
	//終了ボタン
	DrawGraph(180, 700, okbutton, TRUE);
	if (Input::instance()->isClickedRect(200, 700, 400, 750, MOUSE_INPUT_LEFT) == TRUE) {
		startbool = true;
		inventory_menu = -1;
		StopSoundMem(bgm);
		return true;
	}

	//バンパー配置
	button_image(270, 400, 330, 460, 0, gimmick[stock[0]]);
	if (inventory_menu != 2 && inventory_menu != 0)
		button_image(360, 400, 420, 460, 1, gimmick[stock[1]]);
	if (inventory_menu != 3)
		button_image(312, 480, 372, 540, 2, gimmick[stock[2]]);

	//スリングショット
	button_image(120, 570, 190, 670, 3, gimmick[stock[3]]);
	button_image(405, 570, 335, 670, 4, gimmick[stock[4]]);

	//パネル
	button_image(10, 330, 75, 350, 5, gimmick[stock[5]]);

	//押された際のインベントリ処理
	switch (inventory_menu)
	{
	case -1:
		break;
	case 0:
		DrawExtendGraph(330, 440, 545, 300, choice_image, TRUE);
		inventory(340, 310,510,310, gimmick[stock[0]], inventory_menu, stock);
		break;
	case 1:
		DrawExtendGraph(420, 440, 645, 300, choice_image, TRUE);
		inventory(430, 310, 510, 310, gimmick[stock[1]], inventory_menu, stock);
		break;
	case 2:
		DrawExtendGraph(372, 510, 585, 370, choice_image, TRUE);
		inventory(382, 390, 510, 310, gimmick[stock[2]], inventory_menu, stock);
		break;
	case 3:
		DrawExtendGraph(160, 600, 375, 460, choice_image, TRUE);
		inventory(170, 470, 510, 310, gimmick[stock[3]], inventory_menu, stock);
		break;
	case 4:
		DrawExtendGraph(395, 600, 610, 460, choice_image, TRUE);
		inventory(405, 470, 370, 310, gimmick[stock[4]], inventory_menu, stock);
		break;
	case 5:
		DrawExtendGraph(60, 400, 275, 260, choice_image, TRUE);
		inventory( 80, 270, 560, 310, gimmick[stock[5]], inventory_menu, stock);
		break;
	default:
		break;
	}
	return false;
}

void Select::button(int x1,int y1,int x2,int y2,int button) {
	DrawBox(x1, y1, x2, y2, GetColor(255, 255, 255), TRUE);
	if (Input::instance()->isClickedRect(x1, y1, x2, y2, MOUSE_INPUT_LEFT) == TRUE) {
		inventory_menu = button;
	}
}

void Select::button_image(int x1, int y1, int x2, int y2, int button, int image) {
	DrawExtendGraph(x1, y1, x2, y2, image, TRUE);
	if (Input::instance()->isClickedRect(x1, y1, x2, y2, MOUSE_INPUT_LEFT) == TRUE) {
		inventory_menu = button;
	}
}

//インべントリ内のアイテム表示
void Select::inventory(int x1,int y1,int x2,int y2,int imaget,int inventory_menu, int *stock) {
	gimmickcount = 0;
	//削除ボタン
	button_image(x1 + 180, y1, x1 + 210, y1 - 30, -1, chancel);

	if (inventory_menu == 0 || inventory_menu == 1 || inventory_menu == 2) {
		max = 5;
		min = 0;
	}
	else if (inventory_menu == 3 || inventory_menu == 4) {
		max = 9;
		min = 6;
	}
	else if (inventory_menu == 5) {
		max = 11;
		min = 10;
	}

	//アイテムの表示
	for (int i = 0; i <= max ; i++) {
		for (int q = inventory_count[i];q > 0 && i <= max && i >= min; q--) {
			if(gimmickcount == 4) 
				y1 += 60;
			if (gimmickcount >= 4) {
				gimmickcount -= 4;
				over = true;
			}
			DrawExtendGraph(x1 + gimmickcount * 50, y1, x1 + 50 + gimmickcount * 50, y1 + 50, gimmick[i], TRUE);
			if (Input::instance()->isClickedRect(x1 + gimmickcount * 50, y1, x1 + 50 + gimmickcount * 50, y1 + 50, MOUSE_INPUT_LEFT) == TRUE) {
				inventory_count[i]--;
				if(stock[inventory_menu] < 12)
					inventory_count[stock[inventory_menu]]++;
				stock[inventory_menu] = i;
				if (over == true) {
					gimmickcount += 4;
					over = false;
				}
				gimmickcount++;
				//break;
			}
			else {
				if (over == true) {
					gimmickcount += 4;
					over = false;
				}
				gimmickcount++;
			}
			printgimmic[gimmickcount -1] = i;
		}
	}
	for (int q = 0; q < 8; q++) {
		if (printgimmic[q] != -1) {
			if (printgimmic[5] != -1 && over != true) {
				y1 -= 60;
				over = true;
			}
			gimick_detail(printgimmic[q], x1, y1, q);
			printgimmic[q] = -1;
		}
	}
	over = false;
}

void Select::start(int killcount) {
	//bgm再生
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, TRUE);
	if (GetMovieStateToGraph(movie_dieboss[killcount - 1]) != 1) {
		SeekMovieToGraph(movie_dieboss[killcount - 1], 0);
		PlayMovieToGraph(movie_dieboss[killcount - 1]);
		WaitTimer(7);
	}
	switch (killcount){
	case 1:
		for (int i = 0; i <= 1; i++) {
			switch (rand() % 2) {
			case 0:
				inventory_count[3]++;
				break;
			case 1:
				inventory_count[4]++;
				break;
			default:
				break;
			}
		}
		switch (rand() % 2) {
		case 0:
			inventory_count[6]++;
			break;
		case 1:
			inventory_count[7]++;
			break;
		default:
			break;
		}
		startbool = false;
		break;
	case 2:
		for (int i = 0; i <= 1; i++) {
			switch (rand() % 3) {
			case 0:
				inventory_count[1]++;
				break;
			case 1:
				inventory_count[3]++;
				break;
			case 2:
				inventory_count[4]++;
				break;
			default:
				break;
			}
		}
		switch (rand() % 2) {
		case 0:
			inventory_count[6]++;
			break;
		case 1:
			inventory_count[7]++;
			break;
		default:
			break;
		}
		startbool = false;
		break;
	case 3:
		for (int i = 0; i <= 1; i++) {
			switch (rand() % 4) {
			case 0:
				inventory_count[1]++;
				break;
			case 1:
				inventory_count[3]++;
				break;
			case 2:
				inventory_count[4]++;
				break;
			case 3:
				inventory_count[5]++;
				break;
			default:
				break;
			}
		}
		switch (rand() % 3) {
		case 0:
			inventory_count[6]++;
			break;
		case 1:
			inventory_count[7]++;
			break;
		case 2:
			inventory_count[8]++;
		default:
			break;
		}
		switch (rand() % 2) {
		case 0:
			inventory_count[10]++;
			break;
		case 1:
			inventory_count[11]++;
			break;
		default:
			break;
		}
		startbool = false;
		break;
	case 4:
		for (int i = 0; i <= 1; i++) {
			switch (rand() % 4) {
			case 0:
				inventory_count[1]++;
				break;
			case 1:
				inventory_count[3]++;
				break;
			case 2:
				inventory_count[4]++;
				break;
			case 3:
				inventory_count[2]++;
				break;
			default:
				break;
			}
		}
		switch (rand() % 2) {
		case 0:
			inventory_count[8]++;
			break;
		case 1:
			inventory_count[9]++;
			break;
		default:
			break;
		}
		switch (rand() % 2) {
		case 0:
			inventory_count[10]++;
			break;
		case 1:
			inventory_count[11]++;
			break;
		default:
			break;
		}
		startbool = false;
		break;
	default:
		startbool = false;
		break;
	}
}

void Select::gimick_detail(int items, int x1, int y1, int q) {
	if (q >= 4) {
		y1 += 60;
		q -= 4;
	}
	x1 += q * 50 + 10;
	if (Input::instance()->isOnRect(x1, y1, x1 + 50, y1 + 50) == TRUE) {
		x1 -= 90;
		DrawExtendGraph(x1, y1, x1 + 100, y1 + 50, choice_image, TRUE);
		if (items < 10) {
			DrawFormatString(x1, y1 + 30, GetColor(255, 1, 1), "攻撃力 %d", detail[items]);
			DrawFormatString(x1, y1, GetColor(255, 1, 1), "属性 %s", gimmictipe[items]);
		}
		else if (items == 10) {
			DrawFormatString(x1, y1, GetColor(255, 1, 1), "物理攻撃を");
			DrawFormatString(x1, y1 + 30, GetColor(255, 1, 1), "3秒間1.5倍");
		}
		else if (items == 11) {
			DrawFormatString(x1, y1, GetColor(255, 1, 1), "魔法攻撃を");
			DrawFormatString(x1, y1 + 30, GetColor(255, 1, 1), "3秒間1.5倍");
		}
	}
}