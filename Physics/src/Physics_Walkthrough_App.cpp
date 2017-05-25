#include "Physics_Walkthrough_App.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Camera.h"
#include "Physics\PhysicsObject.h"
#include "Physics\PhysicsScene.h"
#include "Physics\PhysicsRenderer.h"
#include "Physics\SphereCollider.h"
#include "Physics\AABBCollider.h"
#include "Physics\Spring.h"
Physics_Walkthrough_App::Physics_Walkthrough_App()
{

}

Physics_Walkthrough_App::~Physics_Walkthrough_App()
{

}

bool Physics_Walkthrough_App::startup()
{
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	aie::Gizmos::create(1000000, 1000000, 1000000, 1000000);

	// create simple camera transforms
	m_camera = new Camera();
	m_camera->SetProjection(glm::radians(45.0f), (float)getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.0f);
	m_camera->SetPosition(glm::vec3(10, 10, 10));
	m_camera->Lookat(glm::vec3(0, 0, 0));

	physicsRenderer = new PhysicsRenderer();
	physicsScene = new PhysicsScene();

	physicsScene->AttachObject(new PhysicsObject(glm::vec3(0.0f,5.0f,0.0f),1.0f,glm::vec3(1.0f),1.0f, true));//Create a new phys object with physics
	physicsScene->GetObjectAt(0)->SetCollider(new AABBCollider(glm::vec3(0.3f,0.3f,0.3f)));

	//physicsScene->AttachObject(new PhysicsObject(glm::vec3(0.0f,0.0f,0.0f), 1.0f, glm::vec3(1.0f), 1.0f));//Create a new phys object
	//physicsScene->GetObjectAt(1)->SetCollider(new AABBCollider(glm::vec3(10.0f,1.0f,10.0f)));

	//for (size_t x = 0; x < 10; x++)
	//{
	//	for (size_t y = 0; y < 1; y++)
	//	{
	//		for (size_t z = 0; z < 10; z++)
	//		{
	//			PhysicsObject* object = new PhysicsObject(true);//Enabling phyiscs
	//			object->SetPosition(glm::vec3(x - 5.0f, y + 10, z - 5.0f));
	//			object->SetCollider(new SphereCollider(0.3f));
	//			physicsScene->AttachObject(object);
	//		}
	//	}
	//}
	//for (size_t x = 0; x < 10; x++)
	//{
	//	for (size_t y = 0; y < 1; y++)
	//	{
	//		for (size_t z = 0; z < 10; z++)
	//		{
	//			PhysicsObject* object = new PhysicsObject(true);//Enabling phyiscs
	//			object->SetPosition(glm::vec3(x - 5.0f, y + 20, z - 5.0f));
	//			object->SetCollider(new AABBCollider(glm::vec3(0.3f)));
	//			physicsScene->AttachObject(object);
	//		}
	//	}
	//}

	/*PhysicsObject* left = new PhysicsObject(true);
	left->SetPosition(glm::vec3(-10, 1, 0));
	left->SetCollider(new SphereCollider(1.0f));
	physicsScene->AttachObject(left);

	PhysicsObject* right = new PhysicsObject(true);
	right->SetPosition(glm::vec3(10, 1, 0));
	right->SetCollider(new SphereCollider(1.0f));
	physicsScene->AttachObject(right);

	PhysicsObject* top = new PhysicsObject(true);
	top->SetPosition(glm::vec3(0, 10, 0));
	top->SetCollider(new SphereCollider(1.0f));
	physicsScene->AttachObject(top);
	
	PhysicsObject* back = new PhysicsObject(true);
	back->SetPosition(glm::vec3(0, -10, 0));
	back->SetCollider(new SphereCollider(1.0f));
	physicsScene->AttachObject(back);

	Spring* spring = new Spring(left, right,7.0f,200,1);
	physicsScene->AttatchConstraint(spring);

	Spring* spring2 = new Spring(left, back, 7.0f, 200, 1);
	physicsScene->AttatchConstraint(spring2);
	
	Spring* spring3 = new Spring(left, top, 7.0f, 200, 1);
	physicsScene->AttatchConstraint(spring3);
	
	Spring* spring4 = new Spring(left, top, 7.0f, 200, 1);
	physicsScene->AttatchConstraint(spring4);
	
	Spring* spring5 = new Spring(right, back, 7.0f, 200, 1);
	physicsScene->AttatchConstraint(spring5);
	
	
	Spring* spring6 = new Spring(top, back, 7.0f, 200, 1);
	physicsScene->AttatchConstraint(spring6);
	
	Spring* spring7 = new Spring(right, top, 7.0f, 200, 1);
	physicsScene->AttatchConstraint(spring7);*/
	const int maxX = 3;
	const int maxY = 3;
	const int maxZ = 3;
	PhysicsObject* blob[maxX][maxY][maxZ];

	for (int x = 0; x < maxX; x++)	//Do Height Last
	{
		for (int y = 0; y < maxY; y++)
		{
			for (int z = 0; z < maxZ; z++)
			{
				PhysicsObject *obj = new PhysicsObject(true);
				obj->SetPosition(glm::vec3(x, y, z));
				obj->SetCollider(new SphereCollider(0.3f));
				blob[x][y][z] = obj;
				physicsScene->AttachObject(obj);
			}
		}
	}

	for (int x = 0; x < maxX; x++)
	{
		for (int y = 0; y < maxY; y++)
		{
			for (int z = 0; z < maxZ; z++)
			{
				if (y < 2)	//Up
				{
					Spring *spring = new Spring(blob[x][y][z], blob[x][y + 1][z], 1, 200, 1);
					physicsScene->AttatchConstraint(spring);
				}
				if (x < 2)	//Right
				{
					Spring *spring = new Spring(blob[x][y][z], blob[x + 1][y][z], 1, 200, 1);
					physicsScene->AttatchConstraint(spring);
				}
				if (z < 2)	//Left
				{
					Spring *spring = new Spring(blob[x][y][z], blob[x][y][z + 1], 1, 200, 1);
					physicsScene->AttatchConstraint(spring);
				}
				//Z and X
				if (z < 2 && x < 2)
				{
					Spring *spring = new Spring(blob[x][y][z], blob[x + 1][y][z + 1], 1.5, 200, 1);
					physicsScene->AttatchConstraint(spring);
				}
				
				if (z < 2 && x < 2)
				{
					Spring *spring = new Spring(blob[x][y][z + 1], blob[x + 1][y][z], 1.5, 200, 1);
					physicsScene->AttatchConstraint(spring);
				}
				//---
				//Z and Y
				if (z < 2 && y < 2)
				{
					Spring *spring = new Spring(blob[x][y][z], blob[x][y + 1][z + 1], 1.5, 200, 1);
					physicsScene->AttatchConstraint(spring);
				}
				if (z < 2 && y < 2)
				{
					Spring *spring = new Spring(blob[x][y + 1][z], blob[x][y][z + 1], 1.5, 200, 1);
					physicsScene->AttatchConstraint(spring);
				}
				//---
				//X and Y
				if (x < 2 && y < 2)
				{
					Spring *spring = new Spring(blob[x][y + 1][z], blob[x  + 1][y][z], 1.5, 200, 1);
					physicsScene->AttatchConstraint(spring);
				}
				if (x < 2 && y < 2)
				{
					Spring *spring = new Spring(blob[x][y][z], blob[x + 1][y  + 1][z], 1.5, 200, 1);
					physicsScene->AttatchConstraint(spring);
				}
				//---
			}
		}
	}

	return true;
}

void Physics_Walkthrough_App::shutdown()
{
	aie::Gizmos::destroy();
	delete m_camera;
	delete physicsRenderer;
	delete physicsScene;
	//Destroy the camera aswell as the Physics object Scene Manager and Renderer
}

void Physics_Walkthrough_App::update(float deltaTime)
{
	m_camera->Update(deltaTime);
	physicsScene->AddForceToAllobjects(glm::vec3(0,-9.8f,0));
	physicsScene->Update(deltaTime);
	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
	if(input->isKeyDown(aie::INPUT_KEY_UP))
		physicsScene->GetObjectAt(0)->ApplyForce(glm::vec3(3, 0, 0));//Apply a force to the object
	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
		physicsScene->GetObjectAt(0)->ApplyForce(glm::vec3(0, 0, 3));//Apply a force to the object
	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
		physicsScene->GetObjectAt(0)->ApplyForce(glm::vec3(-3, 0, 0));//Apply a force to the object
	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
		physicsScene->GetObjectAt(0)->ApplyForce(glm::vec3(0, 0, -3));//Apply a force to the object
	if (input->wasKeyPressed(aie::INPUT_KEY_ENTER)) {
		deleteCount = physicsScene->GetObjects().size() - 1;
		spawnAcross--;
		if(deleteCount >=0)
			physicsScene->RemoveObject(physicsScene->GetObjectAt(deleteCount));
	}
	if (input->wasKeyPressed(aie::INPUT_KEY_BACKSPACE)) {
		physicsScene->AttachObject(new PhysicsObject(glm::vec3(spawnAcross, 5.0f, 1.0f), 1.0f, glm::vec3(1.0f), 1.0f));
		spawnAcross++;
	}
	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT)) {
		PhysicsObject* obj = new PhysicsObject(true,5.0f);//enabling physics
		obj->SetPosition(m_camera->GetPosition());
		obj->SetVelocity(m_camera->GetFront() * 20.0f);
		obj->SetCollider(new SphereCollider(0.5f));
		physicsScene->AttachObject(obj);
	}

}

void Physics_Walkthrough_App::draw()
{
	// wipe the screen to the background colour
	clearScreen();
	// wipe the gizmos clean for this frame
	aie::Gizmos::clear();
	RenderGizmosGrid();
	physicsRenderer->Draw(physicsScene);
	aie::Gizmos::draw(m_camera->GetProjectionView());

}

void Physics_Walkthrough_App::RenderGizmosGrid()
{
	// draw a simple grid with gizmos
	glm::vec4 white(1);
	glm::vec4 black(0, 0, 0, 1);
	for (int i = 0; i < 21; ++i)
	{
		aie::Gizmos::addLine(glm::vec3(-10 + i, 0, 10), glm::vec3(-10 + i, 0, -10), i == 10 ? white : black);
		aie::Gizmos::addLine(glm::vec3(10, 0, -10 + i), glm::vec3(-10, 0, -10 + i), i == 10 ? white : black);
	}

	// add a transform so that we can see the axis
	aie::Gizmos::addTransform(glm::mat4());

}
