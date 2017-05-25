#pragma once
#include "Physics\PhysicsObject.h"
#include "Physics\Constraint.h"
#include "Physics\IntersectData.h"
#include <vector>
#include <glm\glm.hpp>
class PhysicsScene
{
public:
	struct CollisionInfo
	{
		PhysicsObject* objA;
		PhysicsObject* objB;
		IntersectData intersect;
	};
	PhysicsScene();
	virtual ~PhysicsScene() {
		for (auto iter = objects.begin(); iter != objects.end(); ++iter)
		{
			delete *iter;
		}
		objects.clear();
	};
	void Update(float deltaTime);
	void AddForceToAllobjects(const glm::vec3& force);
	bool isObjectColliding(PhysicsObject* object);

	void AttachObject(PhysicsObject* object);
	void AttachAllObjects(std::vector<PhysicsObject*> objects);
	const std::vector<PhysicsObject*>& GetObjects() { return objects; }
	void RemoveObject(PhysicsObject* object);
	PhysicsObject* GetObjectAt(int index) { return objects[index]; }

	void AttatchConstraint(Constraint* con);
	void RemoveConstraint(Constraint* con);
	const std::vector<Constraint*>& GetConstraints() { return constraints; }

protected:
	std::vector<PhysicsObject*> objects;
	std::vector<Constraint*> constraints;
	glm::vec3 globalForce;
	glm::vec3 gravAccel = glm::vec3(0.0f, -0.98f, 0.0f);
private:
	void DetectCollisions();
	void ResolveCollisions();
	std::vector<CollisionInfo> collisions;
};

