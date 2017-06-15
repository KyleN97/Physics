#include "Physics\Collider.h"
#include "Physics\SphereCollider.h"
#include "Physics\AABBCollider.h"
#include "Physics\IntersectData.h"
#include <glm\vec3.hpp>
#include <glm\geometric.hpp>

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

	float distance = glm::length(collisionVector);//Distance between the two objects

	float colDistance = sphere->GetRadius() + other->GetRadius();//Collision distance - radius + radius

	collisionVector =  glm::normalize(collisionVector) * (colDistance - distance);
	intersect->collisionVector = collisionVector;
	return distance <= colDistance;//Check wether the sphere is within collision distance return true if colliding - false if not
}


bool Collider::AABBTOAABBIntersect(const AABBCollider * aabb, const AABBCollider * other,IntersectData* intersect)
{
	bool collision = ((other->GetPosition().x + other->GetSize().x) >= (aabb->GetPosition().x - aabb->GetSize().x) && (aabb->GetPosition().x + aabb->GetSize().x) >= (other->GetPosition().x - other->GetSize().x)) &&
					 ((other->GetPosition().y + other->GetSize().y) >= (aabb->GetPosition().y - aabb->GetSize().y) && (aabb->GetPosition().y + aabb->GetSize().y) >= (other->GetPosition().y - other->GetSize().y)) &&
					 ((other->GetPosition().z + other->GetSize().z) >= (aabb->GetPosition().z - aabb->GetSize().z) && (aabb->GetPosition().z + aabb->GetSize().z) >= (other->GetPosition().z - other->GetSize().z));
	return collision;//Check the points of the AABB's and check if they are overlapping
}

bool Collider::SphereToAABBIntersect(const SphereCollider * sphere, const AABBCollider * aabb,IntersectData* intersect)
{
	auto check = [&](const double pn,const double bmin,const double bmax) -> double
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
	};//Check the spheres position against each point in the AABB

	// Squared distance
	double sq = 0.0;

	sq += check(sphere->GetPosition().x, aabb->GetPosition().x, aabb->GetPosition().x + aabb->GetSize().x);
	sq += check(sphere->GetPosition().y, aabb->GetPosition().y, aabb->GetPosition().y + aabb->GetSize().y);
	sq += check(sphere->GetPosition().z, aabb->GetPosition().z, aabb->GetPosition().z + aabb->GetSize().z);
	

	return sq <= (sphere->GetRadius() * sphere->GetRadius());//Check the returned results against the sphere
}
