#include "Boxing.h"

BoShape::BoShape(std::vector<Vector2> new_points, float new_inertia){
	points = new_points;
	inertia = new_inertia;
	if(points.size() < 3)
		return;
		//Throw exception or smth when there are less then 3 new_points.

	for(std::vector<Vector2>::iterator it = points.begin(); it != points.end(); ++it){
		std::vector<Vector2>::iterator it2 = it + 1;
		if(it2 == points.end())
			it2 = points.begin();
		Vector2 wall = *it2 - *it;
		Vector2 normal;
		normal.x = -wall.y;
		normal.y = wall.x;
		normal.Normalize();
		normals.push_back(normal);
		//walls.push_back(wall);
	}
}

const std::vector<Vector2> BoShape::GetPointArray(){
	return points; //this is good? probably not
}

BoCollision BoShape::TestCollision(const BoShape *shapeA, const BoShape *shapeB, Matrix3 &BSpaceToASpaceTransformation){
	BoCollision collision;
	Matrix3 NormalTransform = BSpaceToASpaceTransformation;
	NormalTransform.m[2][0] = NormalTransform.m[2][1] = NormalTransform.m[0][2] = NormalTransform.m[1][2] = 0.f;
	NormalTransform.m[2][2] = 1.f;
	float TransformedVectorLength = (NormalTransform * Vector2(1.f,0.f)).Length();
	NormalTransform.m[0][0] /= TransformedVectorLength;
	NormalTransform.m[1][0] /= TransformedVectorLength;
	NormalTransform.m[0][1] /= TransformedVectorLength;
	NormalTransform.m[1][1] /= TransformedVectorLength;
	//Now NormalTransform is 'normalized' matrix of rotation only, and will serve the purpose of rotating normals.

	//Initializing all needed values
	float MinDist = 300;
	int MinDistA = -1;
	int MinDistB = -1;
	Vector2 MinDistPoint(0,0);

	for(unsigned int A = 0; A < shapeA->points.size(); A++){
		Vector2 pointA = shapeA->points[A];
		Vector2 normalA = shapeA->normals[A];

		float LocalMinDist = 300;
		int LocalMinDistA = -1;
		int LocalMinDistB = -1;
		Vector2 LocalMinDistPoint(0,0);

		if(shapeB->normals.size() != shapeB->points.size())
			return collision;
		for(unsigned int B = 0; B < shapeB->points.size(); B++){
			Vector2 pointB = BSpaceToASpaceTransformation * shapeB->points[B];
			pointB += pointA; //TODO why? cuz this is good
			Vector2 normalB = NormalTransform * shapeB->normals[B];
			normalB.Normalize();

			float dist = normalA * pointB;
			if(LocalMinDist > dist || LocalMinDistB<0){
				LocalMinDist = dist;
				LocalMinDistA = A;
				LocalMinDistB = B;
				LocalMinDistPoint = pointB;
			}
		}
		if(LocalMinDist > 0.f)
			return collision;
		else{
			if(MinDist < LocalMinDist || MinDistB < 0.f){
				MinDist = LocalMinDist;
				MinDistA = LocalMinDistA;
				MinDistB = LocalMinDistB;
				MinDistPoint = LocalMinDistPoint;
			}
		}

	}

	if(MinDist >= 0.f){
		return collision;
	}

	collision.happended = true;
	collision.Point = MinDistPoint;
	collision.Normal = shapeA->normals[MinDistA];
	collision.time = 0.f;
	collision.overlapping = -MinDist;

	return collision;
}

BoEntity::BoEntity(BoShape *new_shape, float new_mass, float new_inertia){
	position = 0; speed = 0;
	rotation = 0; omega = 0;

	shape = new_shape;
	mass = new_mass;
	inertia = new_inertia;

	if(shape == 0)
		return; //exception

	if(mass <= 0.f)
		return; //exception

	isstatic = false;
}

Vector2 BoEntity::GetPosition(){
	return position;
}

float BoEntity::GetRotation(){
	return rotation;
}

float BoEntity::GetMass(){
	return mass;
}

void BoEntity::SetPosition(const Vector2 &pos){
	position = pos;
}

void BoEntity::SetRotation(const float rot){
	rotation = rot;
}

void BoEntity::SetMass(const float m){
	mass = m;
}

void BoEntity::SetSpeed(const Vector2 &sp){
	speed = sp;
}

void BoEntity::SetOmega(const float o){
	omega = o;
}

BoShape* BoEntity::GetShape(){
	return shape;
}

BoCollision BoWorld::TestCollision(BoEntity* entity1, BoEntity* entity2){
	Matrix3 BToATransformation;
	BToATransformation.Identity();
	BToATransformation.AddRotation(entity2->GetRotation());
	BToATransformation.AddTranslation(entity2->GetPosition());
	BToATransformation.AddTranslation(Vector2(0,0) - entity1->GetPosition());
	BToATransformation.AddRotation(-entity1->GetRotation());

	BoCollision ret = BoShape::TestCollision(entity1->GetShape(), entity2->GetShape(), BToATransformation);

	Matrix3 AToBTransformation;
	AToBTransformation.Identity();
	AToBTransformation.AddRotation(entity1->GetRotation());
	AToBTransformation.AddTranslation(entity1->GetPosition());
	AToBTransformation.AddTranslation(Vector2(0,0) - entity2->GetPosition());
	AToBTransformation.AddRotation(-entity2->GetRotation());
	BoCollision ret2 = BoShape::TestCollision(entity2->GetShape(), entity1->GetShape(), AToBTransformation);
	ret.entity1 = entity1;
	ret.entity2 = entity2;
	ret2.entity1 = entity2;
	ret2.entity2 = entity1;
	if(ret2.happended && ret.happended){
		if(ret2.overlapping < ret.overlapping)
			ret = ret2;
	}
	if(ret.happended && !ret2.happended)
		ret = ret2;

	Matrix3 AtoAbsolute;
	AtoAbsolute.Identity();
	float e = ret.entity1->GetRotation();
	AtoAbsolute.AddRotation(e);
	ret.Normal = AtoAbsolute * ret.Normal;
	Vector2 f = ret.entity1->GetPosition();
	AtoAbsolute.AddTranslation(f);
	ret.Point = AtoAbsolute * ret.Point;
	return ret;
}

void BoWorld::AddEntity(BoEntity* entity){
	entities.push_back(entity);
}


void BoWorld::Simulate(float time){
	if(time <= 0.f)
		return;

	std::vector<BoCollision> collisions;

	for(std::vector<BoEntity*>::iterator i = entities.begin(); i != entities.end(); ++i){
		BoEntity *e = (*i);
		if(!e->isstatic){
			e->position += e->speed * time;
			e->rotation += e->omega * time;

			e->speed += gravity * time;
			e->position += gravity * time * time / 2.f;

			float ground_dist = e->position.y - ground_level;
			if(ground_dist < 0.f){
				e->position.y -= ground_dist;
				e->speed.y *= -0.3f;
				e->speed.x *= 0.7f;
				//e->omega *= 0.7f;
			}
		}

		for(std::vector<BoEntity*>::iterator j = i + 1; j != entities.end(); ++j){
			BoCollision collision = TestCollision(*i, *j);
			if(collision.happended)
				collisions.push_back(collision);
		}
	}

	for(std::vector<BoCollision>::iterator it = collisions.begin(); it != collisions.end(); ++it){
		float TotalRestitution = 0.5f;
		Vector2 CollisionOrigin = it->Point + it->Normal*it->overlapping;
		Vector2 Radius1 = CollisionOrigin - it->entity1->GetPosition();
		Vector2 Radius2 = CollisionOrigin - it->entity2->GetPosition();
		Radius1.Perpendicular();
		Radius2.Perpendicular();
		float r1 = Radius1*it->Normal;
		float r2 = Radius2*it->Normal;
		Vector2 PointSpeed = (it->entity1->speed + Radius1*it->entity1->omega) - (it->entity2->speed + Radius2*it->entity2->omega);
		float Impulse = PointSpeed * it->Normal * (1.0f + TotalRestitution);
		float Slowing = 0.f;
		if(!it->entity1->isstatic)
			Slowing += 1.f/it->entity1->mass + r1*r1/it->entity1->inertia;
		if(!it->entity2->isstatic)
			Slowing += 1.f/it->entity2->mass + r2*r2/it->entity2->inertia;
		Impulse /= Slowing;

		Vector2 b = it->Normal * Impulse;

		if(!it->entity1->isstatic){
			it->entity1->speed -= b/it->entity1->mass;
			it->entity1->omega -= r1*Impulse/it->entity1->inertia;
			it->entity1->position -= it->Normal*it->overlapping/2.f;
		}

		if(!it->entity2->isstatic){
			it->entity2->speed += b/it->entity2->mass;
			it->entity2->omega += r2*Impulse/it->entity2->inertia;
			it->entity2->position += it->Normal*it->overlapping/2.f;
		}

		std::cout << "Kolizja " << Impulse << " point:" << CollisionOrigin.x << "x" << CollisionOrigin.y << " normal:" << it->Normal.x << "x" << it->Normal.y << std::endl;
	}
}
