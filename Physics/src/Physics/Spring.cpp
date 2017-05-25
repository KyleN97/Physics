#include "Physics\Spring.h"
#include "Physics\PhysicsObject.h"
Spring::Spring(PhysicsObject * objA, PhysicsObject * objB) : Constraint(std::vector<PhysicsObject*> {objA, objB},Constraint::Type::SPRING)
{
}

Spring::Spring(PhysicsObject * objA, PhysicsObject * objB, float _length, float _stiffness, float _friction) : 
Constraint(std::vector<PhysicsObject*> {objA, objB}, Constraint::Type::SPRING),
length(_length),
stiffness(_stiffness),
friction(_friction)
{
}

Spring::~Spring() {

}

void Spring::Update(float deltaTime)
{
	PhysicsObject* objA;
	PhysicsObject* objB;
	objA = objects[0];
	objB = objects[1];
	//dist between 2 objects
	glm::vec3 springVec = objB->GetPosition() - objA->GetPosition();
	float distance = glm::length(springVec);
	//create force along vector between them based on how far away we are from length
	glm::vec3 force;
	
	if (distance != 0)
	{
		force += glm::normalize(springVec) * (distance - length) * stiffness;

		force += (glm::dot(objB->GetVelocity() - objA->GetVelocity(),springVec)) * glm::normalize(springVec)* friction;
	}
	//edit that force for friction
	objA->ApplyForce(force);
	objB->ApplyForce(-force);

}