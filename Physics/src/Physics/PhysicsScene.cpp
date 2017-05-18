#include "Physics\PhysicsScene.h"



PhysicsScene::PhysicsScene()
{
}


PhysicsScene::~PhysicsScene()
{
}

void PhysicsScene::Update(float deltaTime)
{
	for each (PhysicsObject* var in objects)
	{
		var->Update(deltaTime);
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
void PhysicsScene::RemoveObject(PhysicsObject * object)
{
	for (std::vector<PhysicsObject*>::iterator iter = objects.begin(); iter != objects.end(); ++iter)
	{
		if (*iter == object)
		{
			objects.erase(iter);
			break;
		}
	}
}
