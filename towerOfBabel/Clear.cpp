#include"clear.h"
#include "Boss.h"

Clear::Clear() {	
	ranc[0] = 0;
	ranc[1] = 0;
	ranc[2] = 0;
	ranc[3] = 0;
	ranc[4] = 0;
	first = true;
	image_clear = 0;
	highscore = 0;
	falsify = false;
	for (int i = 0; i <= 5; i++) {
		for (int q = 0; q <= 23; q++) {
			ranctest[i][q] = 0;
			rancin[i][q] = 0;
		}
	}
	rancs = 0;
	bgm = 0;
	i = 0;
	rancs = 0;
	testranc[0] = 0;
	testranc[1] = 0;
	testranc[2] = 0;
	testranc[3] = 0;
	testranc[4] = 0;
}

bool Clear::Score(int* score, int ball) {
	//初めに行うファイル操作
	if (first == true) {
		first = false;
		//ファイル読み込み
		std::ifstream ifs("menu.txt");
		std::string str;
		//内容を入れる
		char s_scores[144];
		int z = 0;
		if (ifs) {
			while (ifs.get(s_scores[z])) {
				std::cout << s_scores[z];
				if (z == 0) rancin[0][0] = s_scores[z] - 48;
				else rancin[z % 6][z / 6] = s_scores[z] - 48;
				z++;
			}
			//復号
			for (int q = 0; q <= 23; q++) {
				ranctest[0][q] = Xor(rancin[0][q], salt[0][q]);
				ranctest[1][q] = Xor(rancin[1][q], rancin[0][q]);
				ranctest[1][q] = Xor(ranctest[1][q], salt[1][q]);
				ranctest[2][q] = Xor(rancin[2][q], rancin[1][q]);
				ranctest[2][q] = Xor(ranctest[2][q], salt[2][q]);
				ranctest[3][q] = Xor(rancin[3][q], rancin[2][q]);
				ranctest[3][q] = Xor(ranctest[3][q], salt[3][q]);
				ranctest[4][q] = Xor(rancin[4][q], rancin[3][q]);
				ranctest[4][q] = Xor(ranctest[4][q], salt[4][q]);
				ranctest[5][q] = Xor(rancin[5][q], rancin[4][q]);
				ranctest[5][q] = Xor(ranctest[5][q], salt[5][q]);
			}
			//データが変更されていないか
			int mac;
			int decimal = 8388608;
			for (int q = 0; q <= 23; q++) {
				mac = Xor(ranctest[1][q], ranctest[0][q]);
				mac = Xor(ranctest[3][q], mac);
				mac = Xor(ranctest[4][q], mac);
				mac = Xor(ranctest[5][q], mac);
				//2進数を10進数に変換
				ranc[0] += ranctest[0][q] * decimal;
				ranc[1] += ranctest[1][q] * decimal;
				ranc[2] += ranctest[3][q] * decimal;
				ranc[3] += ranctest[4][q] * decimal;
				ranc[4] += ranctest[5][q] * decimal;
				decimal /= 2;
				if (mac != ranctest[2][q]) {
					falsify = true;
				}
			}
			if (falsify == true) {
				ranc[0] = 0;
				ranc[1] = 0;
				ranc[2] = 0;
				ranc[3] = 0;
				ranc[4] = 0;
			}
			
		}
		//ポイントが5位以内に入っているか
		//入っていたら入れ替え
		for (int i = 0; i <= 4; i++) {
			if (*score > ranc[i]) {
				for (int q = 4; q > i; q--) {
					ranc[q] = ranc[q - 1];
				}
				ranc[i] = *score;
				for(int q = i;q <= 4;q++)
					testranc[q] = ranc[q];
				break;
			}
			testranc[i] = ranc[i];
		}
		int max = 8388608;
		//2進数に変換
		for (int q = 0; q <= 23;q++) {
			for (int z = 0; z <= 4; z++) {
				if (ranc[z] >= max) {
					ranc[z] = ranc[z] % max;
					if (z >= 2) {
						ranctest[z+1][q] = 1;
					}else
						ranctest[z][q] = 1;
				}else {
					if (z >= 2) {
						ranctest[z + 1][q] = 0;
					}else {
						ranctest[z][q] = 0;
					}
				}
			}
			max /= 2;
		}
		for (int q = 0; q <= 23; q++) {
			ranctest[2][q] = Xor(ranctest[1][q], ranctest[0][q]);
			ranctest[2][q] = Xor(ranctest[3][q], ranctest[2][q]);
			ranctest[2][q] = Xor(ranctest[4][q], ranctest[2][q]);
			ranctest[2][q] = Xor(ranctest[5][q], ranctest[2][q]);
		}
		//暗号化
		for (int q = 0; q <= 23; q++) {
			ranctest[0][q] = Xor(ranctest[0][q], salt[0][q]);
			ranctest[1][q] = Xor(ranctest[1][q], salt[1][q]);
			ranctest[1][q] = Xor(ranctest[1][q], ranctest[0][q]);
			ranctest[2][q] = Xor(ranctest[2][q], salt[2][q]);
			ranctest[2][q] = Xor(ranctest[2][q], ranctest[1][q]);
			ranctest[3][q] = Xor(ranctest[3][q], salt[3][q]);
			ranctest[3][q] = Xor(ranctest[3][q], ranctest[2][q]);
			ranctest[4][q] = Xor(ranctest[4][q], salt[4][q]);
			ranctest[4][q] = Xor(ranctest[4][q], ranctest[3][q]);
			ranctest[5][q] = Xor(ranctest[5][q], salt[5][q]);
			ranctest[5][q] = Xor(ranctest[5][q], ranctest[4][q]);
		}
		//ファイル書き込み
		std::ofstream ofs("menu.txt");
		if (!ofs)
			std::cin.get();
		for (int q = 0; q <= 23; q++) {
			ofs << ranctest[0][q];
			ofs << ranctest[1][q];
			ofs << ranctest[2][q];
			ofs << ranctest[3][q];
			ofs << ranctest[4][q];
			ofs << ranctest[5][q];
			std::cin.get();
		}
		if (ball != 0) {
			bgm = LoadSoundMem("texture\\clear.mp3");
			image_clear = LoadGraph("texture\\Game Clear.mp4");
		}
		else {
			bgm = LoadSoundMem("texture\\gameover.mp3");
			image_clear = LoadGraph("texture\\Game over.mp4");
		}
		//bgm再生
		PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, TRUE);

		//動画
		if (GetMovieStateToGraph(image_clear) != 1) {
			SeekMovieToGraph(image_clear, 0);
			PlayMovieToGraph(image_clear);
			WaitTimer(7);
		}
	}
	DrawExtendGraph(0, 0, 650, 790, image_clear, FALSE);
	if (GetMovieStateToGraph(image_clear) != 1) {
		SetFontSize(40);
		DrawFormatString(180, 235, (255, 255, 255), "%d", *score);

		DrawFormatString(170, 300, (255, 255, 255), "1位 %d", testranc[0]);
		DrawFormatString(170, 370, (255, 255, 255), "2位 %d", testranc[1]);
		DrawFormatString(170, 440, (255, 255, 255), "3位 %d", testranc[2]);
		DrawFormatString(170, 510, (255, 255, 255), "4位 %d", testranc[3]);
		DrawFormatString(170, 580, (255, 255, 255), "5位 %d", testranc[4]);
		SetFontSize(16);

		if (Input::instance()->isClickedRect(80, 650, 600, 750, MOUSE_INPUT_LEFT) == TRUE) {
			first = true;
			StopSoundMem(bgm);
			return true;
		}
	}
	return false;
}

int Clear::Xor(int x, int y) {
	int z;
	z = x + y;
	if (z == 2) {
		z = 0;
	}
	return z;
}