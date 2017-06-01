#pragma once
#include "Physics\PhysicsObject.h"
#include "Physics\Constraint.h"
#include "Physics\IntersectData.h"
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

		for (auto iter = constraints.begin(); iter != constraints.end(); ++iter)
		{
			delete *iter;
		}
		constraints.clear();
	};

	struct CollisionInfo
	{
		PhysicsObject* objA;
		PhysicsObject* objB;
		IntersectData intersect;
	};

	void Update(float deltaTime);
	void AddForceToAllobjects(const glm::vec3& force);	
	void AttachObject(PhysicsObject* object);
	void AttachAllObjects(std::vector<PhysicsObject*> objects);
	void RemoveObject(PhysicsObject* object);
	void AttatchConstraint(Constraint* con);
	void RemoveConstraint(Constraint* con);

	bool isObjectColliding(PhysicsObject* object);
	const std::vector<PhysicsObject*>& GetObjects() { return objects; }
	PhysicsObject* GetObjectAt(int index) { return objects[index]; }
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

