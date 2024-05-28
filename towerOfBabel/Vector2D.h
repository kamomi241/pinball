#pragma once

//二次元ベクトル
struct Vector2D
{
	double x;
	double y;

	//コンストラクタ
	Vector2D() : x(0.0f), y(0.0f) {}
	Vector2D(double ix, double iy) : x(ix), y(iy) {}
	Vector2D(const Vector2D& v) : x(v.x), y(v.y) {}

	//演算子
	Vector2D operator +(const Vector2D& v) const;
	Vector2D operator -(const Vector2D& v) const;
	Vector2D operator *(double n) const;
	Vector2D operator /(double n) const;
	Vector2D operator +=(const Vector2D& v);
	Vector2D operator -=(const Vector2D& v);
	Vector2D operator *=(double n);
	Vector2D operator /=(double n);

	//マイナスのベクトルを返す
	Vector2D inverse() const;

	//ベクトルの長さを返す
	double length() const;

	//ベクトルの長さの二乗を返す
	double lengthSq() const;

	//ベクトルを正規化
	void normalize();

	//正規化されたベクトルを生成
	Vector2D normalizeVec() const;

	//零ベクトルにする
	void zero();
};

//2つのベクトルの内積を返す
double dot(const Vector2D& v1, const Vector2D& v2);

double cross(const Vector2D& v1, const Vector2D& v2);



/* ベクトル　使い方　テスト
*  Vector2D mouseVec(10,10); int xm; int ym;
*
*
		GetMousePoint(&xm, &ym);
		mouseVec.x = (float)xm;
		mouseVec.y = (float)ym;

		Vector2D test1(0.0f, 0.0f);

		DrawFormatString(100,100,GetColor(200,200,200),"ベクトル1 %.2f, %.2f",test1.x,test1.y);
		DrawFormatString(100, 240, GetColor(200, 200, 200), "マウス %.2f, %.2f", mouseVec.x, mouseVec.y);

		DxLib::DrawCircle((int)test1.x, (int)test1.y, 5, GetColor(255, 255, 30));

		DxLib::DrawCircle((int)mouseVec.x, (int)mouseVec.y, 5, GetColor(30, 250, 30));

		Vector2D test3(test1.normalizeVec());

		Vector2D test4(mouseVec.normalizeVec());

		DrawFormatString(100, 140, GetColor(200, 200, 200), "ベクトル1 %.2f, %.2f", test3.x, test3.y);
		DrawFormatString(100, 160, GetColor(200, 200, 200), "ベクトル2 %.2f, %.2f", test4.x, test4.y);

		mouseVec.normalize(); test1.normalize();

		DrawFormatString(100, 220, GetColor(200, 200, 200), "ベクトル1 %.2f, %.2f", test1.x, test1.y);

		DrawFormatString(100, 200, GetColor(200, 200, 200), "ベクトル内積 %.5f", dot(mouseVec, test1));
*/

