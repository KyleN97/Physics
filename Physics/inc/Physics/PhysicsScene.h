#pragma once
#include "Physics\PhysicsObject.h"
#include "Physics\Constraint.h"
#include "Physics\IntersectData.h"
#include <glm\vec3.hpp>
class PhysicsScene
{
public:
	PhysicsScene() {};
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
	//Delete all objects and constraints
	struct CollisionInfo
	{
		PhysicsObject* objA;
		PhysicsObject* objB;
		IntersectData intersect;
	};

	void Update(float deltaTime);
	void AddForceToAllobjects(const glm::vec3& force);//Used to apply gravity to all objects	
	void AttachObject(PhysicsObject* object);//Attach an objects to the scene
	void AttachAllObjects(std::vector<PhysicsObject*> objects);
	void RemoveObject(PhysicsObject* object);//Remove an object from the scene
	void AttatchConstraint(Constraint* con);//Attach a constraint
	void RemoveConstraint(Constraint* con);//Remove an constraint

	bool isObjectColliding(PhysicsObject* object);//Determine wether any objects are colliding
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

