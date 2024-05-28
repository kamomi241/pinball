#pragma once

#include "Vector2D.h"

//シングルトン
// Input::instance()->(関数)でどこからでも使える。
//
//MOUSE_INPUT_LEFT　　： マウス左ボタン
//MOUSE_INPUT_RIGHT　 ： マウス右ボタン
//MOUSE_INPUT_MIDDLE　： マウス中央ボタン
//



class Input {
public:
	
	//Input();

	static Input* instance();

	static void create();
	static void destroy();

	void mouseCheck();
	void keyboardCheck();
	void inputStatsReset();//画面の切り替え時などに使う。input情報をリセット

	bool isKeyPressed(unsigned char key) const;
	bool isKeyReleased(unsigned char key) const;
	bool isKeyDown(unsigned char key) const;
	bool isKeyUp(unsigned char key) const;
	bool isKeyKeepPressing(unsigned char key) const;

	bool isMousePressed(char button) const;
	bool isMouseReleased(char button) const;
	bool isMouseDown(char button) const;
	bool isMouseUp(char button) const;
	bool isMouseKeepPressing(char button) const;

	bool isOnRect(int x1, int y1, int x2, int y2) const;
	bool isClickedRect(int x1, int y1, int x2, int y2, char button) const;//座標内でタッチしたか

	
	double getMouseX() const;
	double getMouseY() const;
	Vector2D getMouseVector() const;

private:
	static Input* m_instance;

	Input();
	~Input();
	Input(const Input&);

	char m_keyState[256];
	char m_oldKeyState[256];
	char m_mouseState;
	char m_oldMouseState;
	Vector2D m_mousePoint;

	//DxLib用の変数
	int m_intMouseX, m_intMouseY;
};