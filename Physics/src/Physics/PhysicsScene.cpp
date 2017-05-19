#include "Physics\PhysicsScene.h"
#include "Physics\Collider.h"
#include <iostream>

PhysicsScene::PhysicsScene()
{
}

void PhysicsScene::Update(float deltaTime)
{
	for each (PhysicsObject* var in objects)
	{
		var->ApplyForce(globalForce);
		var->Update(deltaTime);
		glm::vec3 pos = var->GetPosition();
		glm::vec3 vel = var->GetVelocity();
		if (isObjectColliding(var)) {
			if (var->GetTag() == "Floor")
			{
				std::cout << "Hit Floor...\n";
				var->SetPosition(glm::vec3(pos.x, 0.0f, pos.z));
				var->SetVelocity(glm::vec3(vel.x, -vel.y, vel.z));
			}
			if (var->GetTag() == "Sphere")
			{
				std::cout << "Hit Sphere...\n";
			}

		}

	}
	globalForce = glm::vec3();
	DetectCollisions();
}

void PhysicsScene::AttachObject(PhysicsObject * object)
{
	objects.push_back(object);
}
void PhysicsScene::AttachAllObjects(std::vector<PhysicsObject*> objects)
{
	for each (PhysicsObject* var in objects)
	{
		AttachObject(var);
	}
}
void PhysicsScene::AddForceToAllobjects(const glm::vec3& force)
{
	globalForce = force;
}
void PhysicsScene::RemoveObject(PhysicsObject * object)
{
	for (auto iter = objects.begin(); iter != objects.end(); ++iter)
	{
		if (*iter == object)
		{
			delete *iter;
			objects.erase(iter);
			break;
		}
	}
}
bool PhysicsScene::isObjectColliding(PhysicsObject * object)
{
	for (auto iter = collisions.begin(); iter != collisions.end(); iter++)
	{
		if ((*iter).objA == object || (*iter).objB == object)
		{
			return true;
		}
	}
	return false;
}
void PhysicsScene::DetectCollisions()
{
	collisions.clear();
	for (auto iterA = objects.begin(); iterA != objects.end(); iterA++)
	{
		PhysicsObject* objA = *iterA;
		for (auto iterB = iterA + 1; iterB != objects.end(); iterB++)
		{
			PhysicsObject* objB = *iterB;
			if (objA->GetCollider()->Intersects(objB->GetCollider()))
			{
				CollisionInfo info;
				info.objA = objA;
				info.objB = objB;
				collisions.push_back(info);
			}
		}
	}
}

