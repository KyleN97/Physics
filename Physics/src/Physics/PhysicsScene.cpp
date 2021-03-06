#include "Physics\PhysicsScene.h"
#include "Physics\Collider.h"
#include <iostream>

void PhysicsScene::Update(float deltaTime)
{
	//update constraints
	for each (Constraint* con in constraints)
	{
		con->Update(deltaTime);
	}
	for each (PhysicsObject* var in objects) {
		glm::vec3 currAccel = var->GetAcceleration();//Grab the objects current acceleration
		var->SetAcceleration(currAccel + gravAccel);//Set its accelartion to its current + gravity
		var->ApplyForce(globalForce);//Apply the global gravity to it
		var->Update(deltaTime);//Update the object
		glm::vec3 pos = var->GetPosition();
		glm::vec3 vel = var->GetVelocity();
		//Grab the objects position and velocity
		if (pos.y < 0.3f) {
			var->SetPosition(glm::vec3(pos.x, 0.3f , pos.z));
			var->SetVelocity(glm::vec3(vel.x, -vel.y, vel.z));
		}
#pragma region Marbles
		if (var->GetTag() == "Marble")
		{
			if (pos.x >= 10.0f)
			{
				var->SetPosition(glm::vec3(pos.x, 0.3f, pos.z));
				//var->SetVelocity(glm::vec3(-vel.x, vel.y, vel.z));
				var->ApplyForce(glm::vec3(-4000, 0, 0));
			}
			if (pos.x <= -10.0f)
			{
				var->SetPosition(glm::vec3(pos.x, 0.3f, pos.z));
				//var->SetVelocity(glm::vec3(-vel.x, vel.y, vel.z));
				var->ApplyForce(glm::vec3(4000, 0, 0));
			}
		}
		//If the object is a marble apply a force to it to keep bouncing off walls
#pragma endregion

		if (var->GetLifetime() == true)
		{
			var->SetLifeTime(var->GetRemainingLifetime() - deltaTime, true);
			if (var->GetRemainingLifetime() <= 0.0f)
			{
				RemoveObject(var);
				break;
			}
		}//If the object is simulating lifetime determine wether it has any left if not destroy it
	}
	globalForce = glm::vec3();//Reset the global force
	DetectCollisions();
	ResolveCollisions();
	//Detect any collisions and then resolve them
}

void PhysicsScene::AttachObject(PhysicsObject * object)
{
	objects.push_back(object);//Push the object back into the vector
}

void PhysicsScene::AddForceToAllobjects(const glm::vec3& force)
{
	globalForce = force;//Set the global force
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
	}//Find the certain object and then destroy it
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

void PhysicsScene::AttatchConstraint(Constraint * con)
{
	auto iter = std::find(constraints.begin(), constraints.end(), con);
	if (iter == constraints.end()) {
		constraints.push_back(con);
	}
	//Push back the constraint into the vector
}

void PhysicsScene::RemoveConstraint(Constraint * con)
{
	auto iter = std::find(constraints.begin(), constraints.end(), con);
	if (iter != constraints.end()) {
		delete *iter;
		constraints.erase(iter);
	}
	//Find the certain constraint and then destroy it
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

			if (objA->GetCollider()->Intersects(objB->GetCollider(), &info.intersect))//If objects are intersecting push it back into the collision list
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
		
		//Go through all collision and applyforce and impacts to the objects based on the intersect data from their collisions
	}
}

