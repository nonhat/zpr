#include "algebra.h"

Vector2::Vector2(){
	x = 0;
	y = 0;
}
Vector2::Vector2(float X, float Y){
	x = X;
	y = Y;
}
Vector2 Vector2::operator=(float val){
	x = val;
	y = val;
	return *this;
}

Vector2 Vector2::operator*(float val){
	Vector2 ret;
	ret.x = x*val;
	ret.y = y*val;
	return ret;
}

Vector2 Vector2::operator/(float val){
	Vector2 ret;
	ret.x = x/val;
	ret.y = y/val;
	return ret;
}

Vector2 Vector2::operator*=(float val){
	x *= val;
	y *= val;
	return *this;
}

Vector2 Vector2::operator/=(float val){
	x /= val;
	y /= val;
	return *this;
}

Vector2 Vector2::operator+(const Vector2 &val){
	Vector2 ret;
	ret.x = x + val.x;
	ret.y = y + val.y;
	return ret;
}

Vector2 Vector2::operator-(const Vector2 &val)const {
	Vector2 ret;
	ret.x = x - val.x;
	ret.y = y - val.y;
	return ret;
}

Vector2 Vector2::operator+=(const Vector2 &val){
	x += val.x;
	y += val.y;
	return *this;
}

Vector2 Vector2::operator-=(const Vector2 &val){
	x -= val.x;
	y -= val.y;
	return *this;
}
/*
Vector2 Cross(Vector2 &val1, Vector2 &val2){
	Vector2 ret;
	ret.x = val1.y*val2.z - val2.y*val1.z;
	ret.y =-val1.x*val2.z + val2.x*val1.z;
	ret.z = val1.x*val2.y - val2.x*val1.y;
	return ret;
}*/

float Vector2::operator*(const Vector2 &val){
	float ret;
	ret = x * val.x;
	ret += y * val.y;
	return ret;
}


float Vector2::Length2(){
	return (*this)*(*this);
}

float Vector2::Length(){
	return sqrtf((*this)*(*this));
}

float Vector2::Distance2(const Vector2 &point){
	Vector2 a = (*this - point);
	return a*a;
}

float Vector2::Distance(const Vector2 &point){
	Vector2 a = (*this - point);
	return sqrtf(a*a);
}

void Vector2::Normalize(){
	*this/=Length();
}

void Vector2::Perpendicular(){
	float X = x;
	float Y = y;
	x = -Y;
	y = X;
	//This is fine.
}

Vector2 Interpolate(Vector2 &val1, Vector2 &val2, float c){
	Vector2 ret;
	ret.x = val1.x + (val2.x-val1.x) * c;
	ret.y = val1.y + (val2.y-val1.y) * c;
	return ret;
}


void Matrix3::Zero(){
	for(int i =0 ; i < 3; i++)
		for(int j = 0; j < 3; j++)
				m[i][j] = 0.f;
}

void Matrix3::Identity(){
	for(int i =0 ; i < 3; i++)
		for(int j = 0; j < 3; j++)
			if(i==j)
				m[i][i] = 1.f;
			else
				m[i][j] = 0.f;
}

Matrix3 Matrix3::operator*(const Matrix3 &val){
	Matrix3 ret;
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++){
			ret.m[i][j] = 0.f;
			for(int k = 0; k < 3; k++){
				ret.m[i][j] += m[k][j] * val.m[i][k];
			}
		}
	return ret;
}

Matrix3 Matrix3::operator*=(const Matrix3 &val){
	Matrix3 temp = *this;
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++){
			m[i][j] = 0.f;
			for(int k = 0; k < 3; k++){
				m[i][j] += temp.m[k][j] * val.m[i][k];
			}
		}
	return *this;
}

Matrix3 Matrix3::operator=(const Matrix3 &val){
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			m[i][j] = val.m[i][j];
	return *this;
}

void Matrix3::FromTranslation(const Vector2 &t){
	Identity();
	m[2][0] = t.x;
	m[2][1] = t.y;
}

void Matrix3::FromTranslation(const float x, const float y){
	Identity();
	m[2][0] = x;
	m[2][1] = y;
}

void Matrix3::FromScaling(const Vector2 &s){
	Identity();
	m[0][0] = s.x;
	m[1][1] = s.y;
}

void Matrix3::FromScaling(const float x, const float y){
	Identity();
	m[0][0] = x;
	m[1][1] = y;
}

void Matrix3::FromRotation(const float angle){
	Identity();
	m[0][0] = m[1][1] = cosf(angle);
	m[0][1] = sinf(angle);
	m[1][0] = -m[0][1];
}


void Matrix3::AddTranslation(const Vector2 &t){
  Matrix3 mat;
  mat.FromTranslation(t);
  (*this) = mat*(*this);
}

void Matrix3::AddTranslation(const float x, const float y){
  Matrix3 mat;
  mat.FromTranslation(x,y);
  (*this) = mat*(*this);
}

void Matrix3::AddScaling(const Vector2 &s){
  Matrix3 mat;
  mat.FromScaling(s);
  (*this) = mat*(*this);
}

void Matrix3::AddScaling(const float x, const float y){
  Matrix3 mat;
  mat.FromScaling(x,y);
  (*this) = mat*(*this);
}

void Matrix3::AddRotation(const float angle){
  Matrix3 mat;
  mat.FromRotation(angle);
  (*this) = mat*(*this);
}

Vector2 Matrix3::operator*(const Vector2 &val){
	Vector2 result;
	result.x = val.x * m[0][0] + val.y * m[1][0] + m[2][0];
	result.y = val.x * m[0][1] + val.y * m[1][1] + m[2][1];
	float z =  val.x * m[0][2] + val.y * m[1][2] + m[2][2];
	result.x/=z;
	result.y/=z;
	return result;
}
