#pragma once
#include "Physics\PhysicsObject.h"
#include <vector>
class PhysicsScene
{
public:
	PhysicsScene();
	virtual ~PhysicsScene();
	void Update(float deltaTime);
	void AttachObject(PhysicsObject* object);
	void AttachAllObjects(std::vector<PhysicsObject*> objects);
	void RemoveObject(PhysicsObject* object);

	std::vector<PhysicsObject*> GetObjects() {return objects;}

protected:
	std::vector<PhysicsObject*> objects;
};

