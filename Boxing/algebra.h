#ifndef ALGEBRAH
#define ALGEBRAH
#include <math.h>
#include <string.h>
#include <stdio.h>

struct Vector2{
	float x;
	float y;

	Vector2();
	Vector2(float X, float Y);

	Vector2 operator=(float val);
	Vector2 operator*(float val);
	Vector2 operator/(float val);
	Vector2 operator*=(float val);
	Vector2 operator/=(float val);

	Vector2 operator+(const Vector2 &val);
	Vector2 operator-(const Vector2 &val) const;
	Vector2 operator+=(const Vector2 &val);
	Vector2 operator-=(const Vector2 &val);

	float operator*(const Vector2 &val);
	float Length2();
	float Length();
	float Distance2(const Vector2 &point);
	float Distance(const Vector2 &point);
	void Normalize();
	void Perpendicular();
};

//Vector2 Cross(Vector2 &val1, Vector2 &val2);
Vector2 Interpolate(Vector2 &val1, Vector2 &val2, float c);

struct Matrix3{
	float m[3][3];

	void Zero();
	void Identity();
	Matrix3 operator*(const Matrix3 &val);
	Matrix3 operator*=(const Matrix3 &val);

	void FromTranslation(const Vector2 &t);
	void FromTranslation(const float x, const float y);
	void FromScaling(const Vector2 &s);
	void FromScaling(const float x, const float y);
	void FromRotation(const float angle);

	void AddTranslation(const Vector2 &t);
	void AddTranslation(const float x, const float y);
	void AddScaling(const Vector2 &s);
	void AddScaling(const float x, const float y);
	void AddRotation(const float angle);

	Vector2 operator*(const Vector2 &val);
	Matrix3 operator=(const Matrix3 &val);
	float* GetFloats();
	void Transpose();
};

#endif
