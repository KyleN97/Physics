#pragma once
#include "Physics\PhysicsObject.h"
#include <vector>
#include <glm\glm.hpp>
class PhysicsScene
{
public:
	PhysicsScene();
	virtual ~PhysicsScene() {
		for (auto iter = objects.begin(); iter != objects.end(); ++iter)
		{
			delete *iter;
		}
		objects.clear();
	};
	void Update(float deltaTime);
	void AttachObject(PhysicsObject* object);
	void AttachAllObjects(std::vector<PhysicsObject*> objects);
	void AddForceToAllobjects(const glm::vec3& force);
	void RemoveObject(PhysicsObject* object);

	const std::vector<PhysicsObject*>& GetObjects() {return objects;}

protected:
	std::vector<PhysicsObject*> objects;
	glm::vec3 globalForce;
};

