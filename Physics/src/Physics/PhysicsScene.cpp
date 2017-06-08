#include "Physics\PhysicsScene.h"
#include "Physics\Collider.h"
#include <iostream>

PhysicsScene::PhysicsScene()
{
}

void PhysicsScene::Update(float deltaTime)
{
	//updatae constraints
	for each (Constraint* con in constraints)
	{
		con->Update(deltaTime);//make sure this update is using deltatime.... or remove it
	}
	//
	for each (PhysicsObject* var in objects) {
		glm::vec3 currAccel = var->GetAcceleration();
		var->SetAcceleration(currAccel + gravAccel);
		var->ApplyForce(globalForce);
		var->Update(deltaTime);
		glm::vec3 pos = var->GetPosition();
		glm::vec3 vel = var->GetVelocity();
		if (pos.y < 0.5f) {
			var->SetPosition(glm::vec3(pos.x, 0.5f, pos.z));
			var->SetVelocity(glm::vec3(vel.x, -vel.y, vel.z));
		}
		if (var->GetLifetime() == true)
		{
			var->SetLifeTime(var->GetRemainingLifetime() - deltaTime, true);
			if (var->GetRemainingLifetime() <= 0.0f)
			{
				RemoveObject(var);
				break;
			}
		}
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
		if ((*iter).objA == object)
		{
			std::cout << (*iter).objA->GetTag() + " is colliding with " + object->GetTag() << std::endl;
			return true;
		}
		else if ((*iter).objB == object)
		{
			std::cout << (*iter).objB->GetTag() + " is colliding with " + object->GetTag() << std::endl;
			return true;
		}
	}
	return false;
}

void PhysicsScene::AttatchConstraint(Constraint * con)
{
	auto iter = std::find(constraints.begin(), constraints.end(), con);
	if (iter == constraints.end()) {
		constraints.push_back(con);
	}
}

void PhysicsScene::RemoveConstraint(Constraint * con)
{
	auto iter = std::find(constraints.begin(), constraints.end(), con);
	if (iter != constraints.end()) {
		delete *iter;
		constraints.erase(iter);
	}
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

		//Change from set position make it dependent on objects mass etc - Massive object vs small object

	}
}

