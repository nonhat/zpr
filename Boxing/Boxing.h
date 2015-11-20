#ifndef BOXINGH
#define BOXINGH

#include <iostream>
#include <vector>
#include "algebra.h"

class BoEntity;
class BoWorld;

class BoCollision{
private:
public:
	BoEntity *entity1, *entity2;
	Vector2 Point;
	Vector2 Normal;
	float time;
	float overlapping;
	bool happended;
};

class BoShape{
private:
	float inertia;
	std::vector<Vector2> points;
	std::vector<Vector2> normals;
	//std::vector<Vector2> walls;
public:
	BoShape(std::vector<Vector2> new_points, float new_inertia);

	const std::vector<Vector2> GetPointArray();

	static BoCollision TestCollision(const BoShape *shapeA, const BoShape *shapeB, Matrix3 &BSpaceToASpaceTransformation);
};

class BoEntity{
friend BoWorld;
private:
	Vector2 position, speed;
	float rotation, omega;
	BoShape *shape;
	float mass, inertia;
public:
	bool isstatic;
	BoEntity(BoShape *new_shape, float new_mass, float new_intertia);

	Vector2 GetPosition();
	float GetRotation();
	float GetMass();
	void SetPosition(const Vector2 &pos);
	void SetRotation(const float rot);
	void SetMass(const float m);
	void SetSpeed(const Vector2 &sp);
	void SetOmega(const float o);
	BoShape* GetShape();
};

class BoWorld{
private:
	BoCollision TestCollision(BoEntity* entity1, BoEntity* entity2);
public:
	Vector2 gravity;
	float ground_level;
	std::vector<BoEntity*> entities;
	void AddEntity(BoEntity* entity);
	void Simulate(float time);
};

#endif
