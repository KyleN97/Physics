#include "Physics\PhysicsObject.h"
#include "Physics\Collider.h"



void PhysicsObject::ApplyForce(glm::vec3 force)
{
	if (this->GetIsPhysicsEnabled())
		this->acceleration += force / mass;
	//if physics is enabled apply acceleration to the object relating to its mass
}
Collider * PhysicsObject::GetCollider()
{
	if (collider == nullptr)
		return Collider::GetNullInstance();
	return collider;
}
void PhysicsObject::SetCollider(Collider * _collider)
{
	delete collider;
	collider = _collider;
	collider->Transform(this);
	//Set the collider of this phys object
}
PhysicsObject::~PhysicsObject()
{
	delete collider;
}
void PhysicsObject::Update(float deltaTime)
{
	if (this->GetIsPhysicsEnabled()) {
		ApplyForce(-velocity * friction);//Slow the object down according to friction
		this->velocity = this->velocity + acceleration * deltaTime;
		this->position = this->position + velocity * deltaTime;
		this->acceleration = glm::vec3();//set acceleration to zero after velocity + position change so we dont keep accelerating
		//if were no longer applying a force
	}
	collider->Transform(this);
}
