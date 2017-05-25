#include "Physics\PhysicsObject.h"
#include "Physics\Collider.h"


PhysicsObject::PhysicsObject()
{
}


PhysicsObject::~PhysicsObject()
{
	delete collider;
}

void PhysicsObject::ApplyForce(glm::vec3 force)
{
	if (this->GetIsPhysicsEnabled())
		this->acceleration += force / mass;
}
Collider * PhysicsObject::GetCollider()
{
	if (collider == nullptr)
	{
		return Collider::GetNullInstance();
	}
	return collider;
}
void PhysicsObject::SetCollider(Collider * _collider)
{
	delete collider;
	collider = _collider;
	collider->Transform(this);
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
