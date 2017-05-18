#include "Physics\PhysicsScene.h"



PhysicsScene::PhysicsScene()
{
}

void PhysicsScene::Update(float deltaTime)
{
	for each (PhysicsObject* var in objects)
	{
		var->Update(deltaTime);
		var->ApplyForce(globalForce);
	}
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
