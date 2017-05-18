#include "Physics\PhysicsScene.h"



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
		if (pos.y < 0.0f)
		{
			var->SetPosition(glm::vec3(pos.x, 0.0f, pos.z));
			var->SetVelocity(glm::vec3(vel.x,-vel.y,vel.z));
		}
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

