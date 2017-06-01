#include "Physics\Collider.h"
#include "Physics\SphereCollider.h"
#include "Physics\AABBCollider.h"
#include "Physics\IntersectData.h"
#include <glm\glm.hpp>
#include <iostream>

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

bool Collider::SphereToSphereIntersect(const SphereCollider * sphere, const SphereCollider * other)
{
	glm::vec3 vSpheres = sphere->GetPosition() - other->GetPosition();
	float distance = glm::length(vSpheres);
	float colDistance = sphere->GetRadius() + other->GetRadius();
	
	return distance <= colDistance;
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
	glm::vec3 collisionVector = (other->GetPosition() + other->GetSize()) - (aabb->GetPosition() + aabb->GetSize());
	intersect->collisionVector = collisionVector;
	return (aabb->GetPosition().x <= other->GetPosition().x  + other->GetSize().x  && aabb->GetPosition().x  + aabb->GetSize().x  >= other->GetPosition().x ) &&
		   (aabb->GetPosition().y <= other->GetPosition().y  + other->GetSize().y  && aabb->GetPosition().y  + aabb->GetSize().y  >= other->GetPosition().y ) &&
		   (aabb->GetPosition().z <= other->GetPosition().z  + other->GetSize().z  && aabb->GetPosition().z  + aabb->GetSize().z  >= other->GetPosition().z );
}

bool Collider::SphereToAABBIntersect(const SphereCollider * sphere, const AABBCollider * aabb,IntersectData* intersect)
{
	glm::vec3 collisionVector = aabb->GetPosition() - sphere->GetPosition();
	//std::cout << "Detecting Sphere\n";

	float distance = glm::length(collisionVector);
	float colDistance = sphere->GetRadius() + aabb->GetSize().x;

	collisionVector = glm::normalize(collisionVector) * (colDistance - distance);
	intersect->collisionVector = collisionVector;
	return distance <= colDistance;
}
