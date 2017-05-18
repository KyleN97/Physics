#include "Physics\PhysicsObject.h"



PhysicsObject::PhysicsObject()
{
}


PhysicsObject::~PhysicsObject()
{
}

void PhysicsObject::ApplyForce(glm::vec3 force)
{
	this->acceleration = force / mass;
}
void PhysicsObject::Update(float deltaTime) 
{
	this->velocity = this->velocity + acceleration * deltaTime;
	this->position = this->position + velocity * deltaTime;
}
