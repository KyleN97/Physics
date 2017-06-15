#pragma once
#include <vector>
#include "Physics\PhysicsObject.h"
class PhysicsObject;
class Constraint
{
public:
	enum class Type {
		SPRING,
		JOINT
	};//Type of constraint
	Constraint();
	Constraint(std::vector<PhysicsObject*>& _objects, Type _type) : objects(_objects), type(_type){}
	virtual ~Constraint() {}
	virtual void Update(float deltaTime) = 0;//Update the constraint

	const std::vector<PhysicsObject*>& GetObjects() { return objects; }
	Type GetType()const { return type; }
protected:
	std::vector<PhysicsObject*> objects;
	Type type;
};

