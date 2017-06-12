#include "Physics\Collider.h"
#include "Physics\SphereCollider.h"
#include "Physics\AABBCollider.h"
#include "Physics\IntersectData.h"
#include <glm\vec3.hpp>
Collider::Collider(Type _type) : type(_type)
{

}


Collider::~Collider()
{
}

Collider * Collider::GetNullInstance()
{
	static Collider collider(Type::NONE);
	//Create one then reference the one created
	return &collider;
}

bool Collider::SphereToSphereIntersect(const SphereCollider * sphere, const SphereCollider * other,IntersectData* intersect)
{
	glm::vec3 collisionVector = other->GetPosition() - sphere->GetPosition();
	//std::cout << "Detecting Sphere\n";

	float distance = glm::length(collisionVector);
	float colDistance = sphere->GetRadius() + other->GetRadius();

	collisionVector =  glm::normalize(collisionVector) * (colDistance - distance);
	intersect->collisionVector = collisionVector;
	return distance <= colDistance;
}


bool Collider::AABBTOAABBIntersect(const AABBCollider * aabb, const AABBCollider * other,IntersectData* intersect)
{
	//glm::vec3 collisionVector = other->GetPosition() - aabb->GetPosition();
	
	//float distance = glm::length(collisionVector);
	//float colDistance = aabb->GetSize().y + other->GetSize().y;
	//collisionVector = glm::normalize(collisionVector) * (colDistance - distance);
	//
	//intersect->collisionVector = collisionVector;
	bool collision = (aabb->GetPosition().x <= other->GetPosition().x + other->GetSize().x  && 
					  aabb->GetPosition().x + aabb->GetSize().x >= other->GetPosition().x) &&
					 (aabb->GetPosition().y <= other->GetPosition().y + other->GetSize().y  && 
					  aabb->GetPosition().y + aabb->GetSize().y >= other->GetPosition().y) &&
					 (aabb->GetPosition().z <= other->GetPosition().z + other->GetSize().z  && 
					  aabb->GetPosition().z + aabb->GetSize().z >= other->GetPosition().z);
	//std::cout << "collidied = " + std::to_string(collision )<< std::endl;
	return collision;
}

bool Collider::SphereToAABBIntersect(const SphereCollider * sphere, const AABBCollider * aabb,IntersectData* intersect)
{
	auto check = [&](
		const double pn,
		const double bmin,
		const double bmax) -> double
	{
		double out = 0;
		double v = pn;

		if (v < bmin)
		{
			double val = (bmin - v);
			out += val * val;
		}

		if (v > bmax)
		{
			double val = (v - bmax);
			out += val * val;
		}

		return out;
	};

	// Squared distance
	double sq = 0.0;

	sq += check(sphere->GetPosition().x, aabb->GetPosition().x, aabb->GetPosition().x + aabb->GetSize().x);
	sq += check(sphere->GetPosition().y, aabb->GetPosition().y, aabb->GetPosition().y + aabb->GetSize().y);
	sq += check(sphere->GetPosition().z, aabb->GetPosition().z, aabb->GetPosition().z + aabb->GetSize().z);

	double squaredDistance = sq;

	glm::vec3 collisionVector = sphere->GetPosition() + aabb->GetPosition();

	intersect->collisionVector = glm::normalize(collisionVector) * (glm::length(collisionVector) * aabb->GetSize() + sphere->GetRadius());
	return squaredDistance <= (sphere->GetRadius() * sphere->GetRadius());
}
