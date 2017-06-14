#define GLM_SWIZZLE
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
#include <iostream>
#include <imgui.h>
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

	physicsScene->AttachObject(new PhysicsObject(glm::vec3(5.0f, 0.0f, 0.0f), 1.0f, glm::vec3(1.0f), 1.0f, true));//Create a new phys object with physics
	physicsScene->GetObjectAt(0)->SetCollider(new AABBCollider(glm::vec3(1.0f, 1.0f, 1.0f)));
	physicsScene->GetObjectAt(0)->SetTag("Cube1");


	physicsScene->AttachObject(new PhysicsObject(glm::vec3(-5.0f, 0.0f, 1.0f), 1.0f, glm::vec3(1.0f), 1.0f, true));//Create a new phys object with physics
	physicsScene->GetObjectAt(1)->SetCollider(new SphereCollider(0.3f));
	physicsScene->GetObjectAt(1)->SetTag("Marble");

	physicsScene->AttachObject(new PhysicsObject(glm::vec3(-5.0f, 0.0f, 2.0f), 1.0f, glm::vec3(1.0f), 1.0f, true));//Create a new phys object with physics
	physicsScene->GetObjectAt(2)->SetCollider(new SphereCollider(0.3f));
	physicsScene->GetObjectAt(2)->SetTag("Marble");

	physicsScene->AttachObject(new PhysicsObject(glm::vec3(-5.0f, 0.0f, 3.0f), 1.0f, glm::vec3(1.0f), 1.0f, true));//Create a new phys object with physics
	physicsScene->GetObjectAt(3)->SetCollider(new SphereCollider(0.3f));
	physicsScene->GetObjectAt(3)->SetTag("Marble");

	physicsScene->AttachObject(new PhysicsObject(glm::vec3(-5.0f, 0.0f, 4.0f), 1.0f, glm::vec3(1.0f), 1.0f, true));//Create a new phys object with physics
	physicsScene->GetObjectAt(4)->SetCollider(new SphereCollider(0.3f));
	physicsScene->GetObjectAt(4)->SetTag("Marble");

	physicsScene->AttachObject(new PhysicsObject(glm::vec3(-5.0f, 0.0f, 5.0f), 1.0f, glm::vec3(1.0f), 1.0f, true));//Create a new phys object with physics
	physicsScene->GetObjectAt(5)->SetCollider(new SphereCollider(0.3f));
	physicsScene->GetObjectAt(5)->SetTag("Marble");
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
				obj->SetTag("Blob ball " + std::to_string(x) + std::to_string(y) + std::to_string(z));
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
					Spring *spring = new Spring(blob[x][y + 1][z], blob[x + 1][y][z], 1.5, 200, 1);
					physicsScene->AttatchConstraint(spring);
				}
				if (x < 2 && y < 2)
				{
					Spring *spring = new Spring(blob[x][y][z], blob[x + 1][y + 1][z], 1.5, 200, 1);
					physicsScene->AttatchConstraint(spring);
				}
				//---
				//x and y and z
				if (x < 2 && y < 2 && z < 2)
				{
					Spring *spring = new Spring(blob[x][y][z], blob[x + 1][y + 1][z + 1], 1.5, 200, 1);
					physicsScene->AttatchConstraint(spring);
				}
				if (x < 2 && y < 2 && z < 2)
				{
					Spring *spring = new Spring(blob[x][y + 1][z], blob[x + 1][y][z + 1], 1.5, 200, 1);
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

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
	if (input->isKeyDown(aie::INPUT_KEY_UP))
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
		if (deleteCount >= 0)
			physicsScene->RemoveObject(physicsScene->GetObjectAt(deleteCount));
		//for each (PhysicsObject* var in physicsScene->GetObjects())
		//{
		//	if (var->GetTag() == "Marble")
		//	{
		//		var->ApplyForce(glm::vec3(2000, 0, 0));

		//	}
		//}

	}
	if (input->wasKeyPressed(aie::INPUT_KEY_BACKSPACE)) {
		physicsScene->AttachObject(new PhysicsObject(glm::vec3(spawnAcross, 5.0f, 1.0f), 1.0f, glm::vec3(1.0f), 1.0f));
		spawnAcross++;
	}
	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT)) {
	//	PhysicsObject* obj = new PhysicsObject(true,2.0f);//enabling physics
	//	obj->SetPosition(m_camera->GetPosition());
	//	obj->SetVelocity(m_camera->GetFront() * 20.0f);
	//	obj->SetCollider(new SphereCollider(0.5f));
	//	obj->SetTag("Shotball");
	//	physicsScene->AttachObject(obj);
	//	std::cout<< "Shot ball\n";

	}

	ImGui::Begin("Object Manager");
	static int selection = 0;
	const char* listOfItems[] = { "Sphere","AABB" };
	ImGui::ListBox("Type of Object", &selection, listOfItems, sizeof(listOfItems) / sizeof(listOfItems[0]),3);
	ImGui::InputFloat3("Object Position", positionObject);
	ImGui::Checkbox("Object Gravity?", &gravityObject);
	ImGui::InputFloat("Object LifeTime - zero = Unlimited", &lifetimeObject);
	if (ImGui::Button("Create Object"))
	{
		if (lifetimeObject == 0) {
			PhysicsObject *obj = new PhysicsObject(gravityObject);
			obj->SetPosition(glm::vec3(positionObject[0], positionObject[1], positionObject[2]));
			if (selection == 1)
				obj->SetCollider(new AABBCollider(glm::vec3(1.0f)));
			else
				obj->SetCollider(new SphereCollider(0.3f));
			physicsScene->AttachObject(obj);
		}
		else {
			PhysicsObject *obj = new PhysicsObject(gravityObject, lifetimeObject);
			obj->SetPosition(glm::vec3(positionObject[0], positionObject[1], positionObject[2]));
			if (selection == 1)
				obj->SetCollider(new AABBCollider(glm::vec3(1.0f)));
			else
				obj->SetCollider(new SphereCollider(0.3f));
			physicsScene->AttachObject(obj);

		}
	}
	ImGui::End();


	m_camera->Update(0.016f);//Passing in delta time no need for physics as if we drag window time between frames will be massive and cause everything to fling around
	physicsScene->AddForceToAllobjects(glm::vec3(0, -9.8f, 0));
	physicsScene->Update(0.016f);//Passing in delta time no need for physics as if we drag window time between frames will be massive and cause everything to fling around
	ImGui::Begin("Object Manipulator");
	ImGui::Checkbox("Mouse to Drag Objects", &affectObjects);
	if (affectObjects){
		for each (PhysicsObject* var in physicsScene->GetObjects())
		{
			if ((int)m_camera->mouse_click_callback(input->getMouseX(), input->getMouseY()).x == (int)(var->GetPosition().x))
			{
				var->SetPosition(m_camera->mouse_click_callback(input->getMouseX(), input->getMouseY()));
			}
		}
	}
	ImGui::End();
	//ImGui::Begin("Object Data");
	//for each (PhysicsObject* var in physicsScene->GetObjects())
	//{
	//	const char* type = var->GetTag().c_str();
	//	const char* velocityx = std::to_string(var->GetVelocity().x).c_str();
	//	const char* velocityy = std::to_string(var->GetVelocity().y).c_str();
	//	const char* velocityz = std::to_string(var->GetVelocity().z).c_str();
	//	ImGui::Text(type);
	//	ImGui::Text(velocityx);
	//	ImGui::Text(velocityy);
	//	ImGui::Text(velocityz);
	//}
	//ImGui::End();
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
