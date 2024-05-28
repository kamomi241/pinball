#include "Boss.h"

Boss::Boss() {
	muki[0] = LoadGraph("texture\\startmuki.mp4");
	muki[1] = LoadGraph("texture\\mukimuki.mp4");
	muki[2] = LoadGraph("texture\\endmuki.mp4");
	dief = LoadGraph("texture\\dief.mp4");
	image_boss[0] = LoadGraph("texture\\slim.mp4");
	image_boss[1] = LoadGraph("texture\\fox.mp4");
	image_boss[2] = LoadGraph("texture\\dog.mp4");
	image_boss[3] = LoadGraph("texture\\die.mp4");
	image_boss[4] = LoadGraph("texture\\boss.mp4");
	movie_cameboss[0] = LoadGraph("texture\\cameslime.mp4");
	movie_cameboss[1] = LoadGraph("texture\\camefox.mp4");
	movie_cameboss[2] = LoadGraph("texture\\camedog.mp4");
	movie_cameboss[3] = LoadGraph("texture\\camedie.mp4");
	movie_cameboss[4] = LoadGraph("texture\\cameboss.mp4");
	sound_gimick[0] = LoadSoundMem("effect\\hari.mp3");
	sound_gimick[1] = LoadSoundMem("effect\\ken.mp3");
	sound_gimick[2] = LoadSoundMem("effect\\kamiken.mp3");
	sound_gimick[3] = LoadSoundMem("effect\\steki.mp3");
	sound_gimick[4] = LoadSoundMem("effect\\hon.mp3");
	sound_gimick[5] = LoadSoundMem("effect\\tue.mp3");
	sound_gimick[6] = LoadSoundMem("effect\\kisan.mp3");
	sound_gimick[7] = LoadSoundMem("effect\\san.mp3");
	sound_gimick[8] = LoadSoundMem("effect\\aosan.mp3");
	sound_gimick[9] = LoadSoundMem("effect\\akasan.mp3");
	sound_gimick[10] = LoadSoundMem("effect\\panel.mp3");
	sound_gimick[11] = LoadSoundMem("effect\\panel.mp3");
	damage = 0;
	efecthit = 0;
	time_m = 0;
	effects = 0;
	ex = 0;
	ey = 0;
	moviestart = 0;
	nowhp = 0;
	shield = 0;
	starttime = 0;
	timecount = 0;
	effect = new Effect();
	effectstop = 0;
	killcount = 0;
	type = 0;
	x = 0;
	srand((int)time(NULL));
	y = 0;
	time_s = 0;
	startmove = true;
	randatack = 0;
	dietime = 0;
	beforlife = 0;
}

//開始時に1度動く
void Boss::start(int life) {
	nowhp = boss_type[killcount][0];
	startmove = false;
	x = 0;
	y = 0;
	mukif = false;
	mukicount = 0;
	starttime = clock();
	moviestart = true;
	//敵の登場演出
	if (GetMovieStateToGraph(movie_cameboss[killcount]) != 1) {
		SeekMovieToGraph(movie_cameboss[killcount], 0);
		PlayMovieToGraph(movie_cameboss[killcount]);
		WaitTimer(7);
	}
	dietime = 0;
	beforlife = life;
}
//表示
void Boss::draw(int* bossmove) {
	if (GetMovieStateToGraph(image_boss[killcount]) != 1) {
		SeekMovieToGraph(image_boss[killcount], 0);
		PlayMovieToGraph(image_boss[killcount]);
		WaitTimer(7);
	}
	if (killcount == 0 && nowhp <= 150) {
		if (GetMovieStateToGraph(muki[mukicount]) != 1 && mukif == true) {
			SeekMovieToGraph(muki[1], 0);
			PlayMovieToGraph(muki[1]);
			WaitTimer(7);
			mukicount = 1;
			boss_type[killcount][1] = 0;
		}
		if (GetMovieStateToGraph(muki[0]) != 1 && mukif == false) {
			SeekMovieToGraph(muki[0], 0);
			PlayMovieToGraph(muki[0]);
			WaitTimer(7);
			*bossmove = 205;
			boss_type[killcount][1] += 1000;
			mukif = true;
		}
		DrawExtendGraph(0, 0, 650, 200, muki[mukicount], FALSE);
	}
	else if (GetMovieStateToGraph(dief) == 1) {
		DrawExtendGraph(0, 0, 650, 200, dief, FALSE);
	}
	else
		DrawExtendGraph(0, 0, 650, 200, image_boss[killcount], FALSE);
}
void Boss::move(int time_s ,int* life,int* bossmove) {
	if (dietime + 10000 <= clock() && killcount == 3 && dietime != 0) {
		if (GetMovieStateToGraph(dief) != 1) {
			SeekMovieToGraph(dief, 0);
			PlayMovieToGraph(dief);
			WaitTimer(7);
		}
		*life -= 1;
	}
	if (*life != beforlife) {
		beforlife--;
		dietime = clock();
	}
	if (time_s % 2 == 0) {
		randatack = GetRand(200);
	}
	else {
		*bossmove = randatack;
	}
	if (killcount == 1 && *bossmove <= 50) *bossmove = 201;
	if (killcount == 1 && *bossmove >= 150) *bossmove = 204;
	if (killcount == 0 && *bossmove <= 50 && nowhp <= 150) *bossmove = 202;
	if (killcount == 2 && *bossmove <= 50) *bossmove = 203;
}
//ぎっみくに当たった際の処理
void Boss::hp(int* stock, int hit,int *score,int* life,int* bossmove) {
	//存在しないギミックを省く
	if (hit == -1 || (hit == 5 && stock[5] == 12)) {
		damage = 0;
		type = 0;
	}
	else {
		//ギミック音
		PlaySoundMem(sound_gimick[stock[hit]], DX_PLAYTYPE_BACK, TRUE);
		//ギミックの情報
		damage = gimickatack[stock[hit]];

		type = gimicktype[stock[hit]];
		effects = stock[hit];

		*score += damage;
		//エフェクトが出ているかの確認
		if (effectstop == 0) {
			effectstop = clock() + effecttime[stock[hit]];
			efecthit = hit;
		}
		//ボスへのダメージ
		if (killcount == 3 && *bossmove == 1 || killcount == 4 && *bossmove == 1 || (killcount == 1 || killcount == 2)&& rand() % 4 == 0) {
			SetFontSize(40);
			DrawFormatString(200 + rand() % 100, 100 - rand() % 100, GetColor(255, 255, 255), "ミス！\n");
			SetFontSize(16);
			dietime = clock();
		}
		else {
			dietime = clock();
			if (boss_type[killcount][1] <= 0) {
				boss_type[killcount][1] = 0;
				nowhp -= damage;
			}
			else
				if (type == 0)
					boss_type[killcount][1] -= damage;
				else
					boss_type[killcount][1] -= damage * 3;
		}
	}
	//エフェクトの表示
	if (effectstop >= clock()) {
		switch (efecthit)
		{
		case 0:
			ey = 40;
			ex = 270;
			break;
		case 1:
			ey = 40;
			ex = 360;
			break;
		case 2:
			ey = 50;
			ex = 312;
			break;
		case 3:
			ey = 230;
			ex = 155;
			break;
		case 4:
			ey = 230;
			ex = 370;
			break;
		case 5:
			ey = 30;
			ex = 60;
			break;
		default:
			break;
		}
		if (clock() - effectstop <= 300 ) {
			ey -= (clock() - effectstop) / 3;
		}
		effect->Choice(ex, ey,stock[efecthit]);
	}
	//エフェクトの時間の確認
	else if (effectstop < clock()) {
		effectstop = 0;
	}
	DrawBox(100, 170, (int)(((double)nowhp / (double)boss_type[killcount][0]) * 400.0)
		+ 100, 180, GetColor(255,255,255), TRUE);
	//シールドの表示
	DrawBox(100, 170, 100 + boss_type[killcount][1] / 5, 180, GetColor(0, 67, 255), TRUE);
}

bool Boss::update(int* time, int* stock, int hit, int* score,int* life,int*bossmove) {
	if (startmove == true) {
		start(*life);
	} 
	//登場演出が止まっているかの確認
	if (GetMovieStateToGraph(movie_cameboss[killcount]) != 1) {
		draw(bossmove);
		hp(stock, hit, score,life,bossmove);
		DrawBox(0, 3, 80, 28, GetColor(40, 40, 40), TRUE);
		time_s = (int)((clock() - starttime) / CLOCKS_PER_SEC + *time);
		if (time_s >= 60) {
			time_m = time_s / 60;
			time_s %= 60;
		}
		//時間、スコアの表示
		//DrawFormatString(580, 210, GetColor(255, 255, 255), "%02d:%02d\n", time_m, time_s);
		DrawFormatString(10, 20, GetColor(255, 255, 255), "Score %d\n",*score);
		move(time_s,life,bossmove);
		//ボス撃破
		if (nowhp <= 0) {
			if (killcount == 4) {
				time_m = 0;
				time_s = 0;
			}
			*time = time_m * 60 + time_s;
			*score += scorepoint[killcount] / (clock() - starttime);
			killcount++;
			startmove = true;
			return true;
		}
	}
	else 
		DrawExtendGraph(0, 0, 650, 200, movie_cameboss[killcount], FALSE);
	return false;
}

int* Boss::getkillcount() {
	return &killcount;
}