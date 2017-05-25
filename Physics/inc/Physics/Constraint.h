#pragma once
#include <vector>
class PhysicsObject;
class Constraint
{
public:
	enum class Type {
		SPRING,
		JOINT
	};
	Constraint();
	Constraint(std::vector<PhysicsObject*>& _objects,Type _type);
	virtual ~Constraint();
	virtual void Update(float deltaTime) = 0;

	const std::vector<PhysicsObject*>& GetObjects() { return objects; }
	Type GetType()const { return type; }
protected:
	std::vector<PhysicsObject*> objects;
	Type type;
private:

};

