#pragma once
#include "Physics\PhysicsObject.h"
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
	void AttachObject(PhysicsObject* object);
	void AttachAllObjects(std::vector<PhysicsObject*> objects);
	void AddForceToAllobjects(const glm::vec3& force);
	void RemoveObject(PhysicsObject* object);
	const std::vector<PhysicsObject*>& GetObjects() {return objects;}
	PhysicsObject* GetObjectAt(int index) { return objects[index]; }
	bool isObjectColliding(PhysicsObject* object);
protected:
	std::vector<PhysicsObject*> objects;
	glm::vec3 globalForce;
private:
	void DetectCollisions();
	void ResolveCollisions();
	std::vector<CollisionInfo> collisions;
};

