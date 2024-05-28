#include "Vector2D.h"
#include <cmath>

double Vector2D::length() const
{
	return std::sqrt(x * x + y * y);
}

double Vector2D::lengthSq() const
{
	return x * x + y * y;
}

void Vector2D::normalize()
{
	double len = sqrt(this->x * this->x + this->y * this->y);
	if (len == 0.0f) { this->x = 0.0f; this->y = 0.0f; }
	else
	{
		this->x /= len;
		this->y /= len;
	}
}

Vector2D Vector2D::normalizeVec() const
{
	double len = sqrt(this->x * this->x + this->y * this->y);
	if (len == 0.0f) return Vector2D(0.0f, 0.0f);
	double x = this->x / len;
	double y = this->y / len;
	return Vector2D(x, y);
}

void Vector2D::zero()
{
	this->x = 0.0;
	this->y = 0.0;
}

Vector2D Vector2D::inverse() const
{
	return Vector2D(-this->x, -this->y);
}

double dot(const Vector2D& v1, const Vector2D& v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

double cross(const Vector2D& v1, const Vector2D& v2)
{
	return v1.x * v2.y - v1.y * v2.x;
}

Vector2D Vector2D::operator +(const Vector2D& v) const
{
	return Vector2D(this->x + v.x, this->y + v.y);
}

Vector2D Vector2D::operator -(const Vector2D& v) const
{
	return Vector2D(this->x - v.x, this->y - v.y);
}

Vector2D Vector2D::operator *(double n) const
{
	return Vector2D(this->x * n, this->y * n);
}

Vector2D Vector2D::operator /(double n) const
{
	return Vector2D(this->x / n, this->y / n);
}

Vector2D Vector2D::operator +=(const Vector2D& v)
{
	this->x += v.x;
	this->y += v.y;
	return *this;
}

Vector2D Vector2D::operator -=(const Vector2D& v)
{
	this->x -= v.x;
	this->y -= v.y;
	return *this;
}

Vector2D Vector2D::operator *=(double n)
{
	this->x *= n;
	this->y *= n;
	return *this;
}

Vector2D Vector2D::operator /= (double n)
{
	this->x /= n;
	this->y /= n;
	return *this;
}
