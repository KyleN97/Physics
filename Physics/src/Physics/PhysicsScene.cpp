#include "Physics\PhysicsScene.h"
#include "Physics\Collider.h"
#include <iostream>

PhysicsScene::PhysicsScene()
{
}

void PhysicsScene::Update(float deltaTime)
{
	for each (PhysicsObject* var in objects) {
		var->ApplyForce(globalForce);
		var->Update(deltaTime);
		glm::vec3 pos = var->GetPosition();
		glm::vec3 vel = var->GetVelocity();
		//if (isObjectColliding(var)) {
		if (pos.y < 0.0f) {
			var->SetPosition(glm::vec3(pos.x, 0.0f, pos.z));
			var->SetVelocity(glm::vec3(vel.x, -vel.y, vel.z));
		}

		//}
	}
	globalForce = glm::vec3();
	DetectCollisions();
	ResolveCollisions();
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
			CollisionInfo info;

			if (objA->GetCollider()->Intersects(objB->GetCollider(), &info.intersect))
			{
				info.objA = objA;
				info.objB = objB;
				collisions.push_back(info);
			}
		}
	}
}

void PhysicsScene::ResolveCollisions()
{
	for (auto iter = collisions.begin(); iter != collisions.end(); iter++)
	{
		glm::vec3 colNormal = iter->intersect.collisionVector;

		float massA = iter->objA->GetMass();
		float massB = iter->objB->GetMass();

		glm::vec3 velA = iter->objA->GetVelocity();
		glm::vec3 velB = iter->objB->GetVelocity();

		glm::vec3 relVel = velA - velB;

		glm::vec3 colVector = colNormal * (glm::dot(relVel, colNormal));

		glm::vec3 impulse = colVector / ((1.0f / massA) + (1.0f / massB));

		iter->objA->ApplyForce(impulse);
		iter->objB->ApplyForce(-impulse);

		glm::vec3 seperate = iter->intersect.collisionVector  * 0.5f;

		iter->objA->SetPosition(iter->objA->GetPosition() - seperate);
		iter->objB->SetPosition(iter->objB->GetPosition() + seperate);

	}
}

