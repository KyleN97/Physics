#pragma once
#include "Physics\Constraint.h"
class Spring: public Constraint {

public:
	Spring(PhysicsObject* objA, PhysicsObject* objB) : Constraint(std::vector<PhysicsObject*> {objA, objB}, Constraint::Type::SPRING){}
	Spring(PhysicsObject* objA, PhysicsObject* objB,float _length,float _stiffness,float _friction) :
		Constraint(std::vector<PhysicsObject*> {objA, objB}, Constraint::Type::SPRING),
		length(_length),
		stiffness(_stiffness),
		friction(_friction){}
	virtual ~Spring() {}
	void Update(float deltaTime);
protected:
	float length, stiffness, friction;
};