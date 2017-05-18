#include "Physics\PhysicsObject.h"



PhysicsObject::PhysicsObject()
{
}


PhysicsObject::~PhysicsObject()
{
}

void PhysicsObject::ApplyForce(glm::vec3 force)
{
	this->acceleration += force / mass;
}
void PhysicsObject::Update(float deltaTime) 
{
	ApplyForce(-velocity * friction);//Slow the object down according to friction
	this->velocity = this->velocity + acceleration * deltaTime;
	this->position = this->position + velocity * deltaTime;
	this->acceleration = glm::vec3();//set acceleration to zero after velocity + position change so we dont keep accelerating
	//if were no longer applying a force
}
