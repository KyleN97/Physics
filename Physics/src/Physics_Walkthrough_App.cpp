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
#include <GLFW\glfw3.h>
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

	//Create two testing Cubes
	physicsScene->AttachObject(new PhysicsObject(glm::vec3(5.0f, 0.0f, 0.0f), 1.0f, glm::vec3(1.0f), 1.0f, true));//Create a new phys object with physics
	physicsScene->GetObjectAt(0)->SetCollider(new AABBCollider(glm::vec3(0.3f)));
	physicsScene->GetObjectAt(0)->SetTag("Cube1");

	physicsScene->AttachObject(new PhysicsObject(glm::vec3(8.0f, 0.0f, 0.0f), 1.0f, glm::vec3(1.0f), 1.0f, true));//Create a new phys object with physics
	physicsScene->GetObjectAt(1)->SetCollider(new AABBCollider(glm::vec3(0.3f)));
	physicsScene->GetObjectAt(1)->SetTag("Cube2");

	//Create Marbles
	for (size_t i = 2; i <= 7; i++)
	{
		physicsScene->AttachObject(new PhysicsObject(glm::vec3(-5.0f, 0.0f, i - 1), 1.0f, glm::vec3(1.0f), 1.0f, true));//Create a new phys object with physics
		physicsScene->GetObjectAt(i)->SetCollider(new SphereCollider(0.3f));
		physicsScene->GetObjectAt(i)->SetTag("Marble");
	}


#pragma region CreateBlob
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
				obj->SetTag("Blob ball");
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
#pragma endregion


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
	//Move the first object with UP LEFT DOWN RIGHT - Applying force to it
	if (input->isKeyDown(aie::INPUT_KEY_UP))
		physicsScene->GetObjectAt(0)->ApplyForce(glm::vec3(3, 0, 0));//Apply a force to the object
	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
		physicsScene->GetObjectAt(0)->ApplyForce(glm::vec3(0, 0, 3));//Apply a force to the object
	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
		physicsScene->GetObjectAt(0)->ApplyForce(glm::vec3(-3, 0, 0));//Apply a force to the object
	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
		physicsScene->GetObjectAt(0)->ApplyForce(glm::vec3(0, 0, -3));//Apply a force to the object
	//Each time enter is pressed it will destroy the latest created item
	if (input->wasKeyPressed(aie::INPUT_KEY_ENTER)) {
		deleteCount = physicsScene->GetObjects().size() - 1;
		spawnAcross--;
		if (deleteCount >= 0) {
			if (physicsScene->GetObjectAt(deleteCount)->GetTag() == "Blob ball")
			{
				std::vector<PhysicsObject*> objects = physicsScene->GetObjects();
				for each (PhysicsObject* var in objects)
				{
					if (var->GetTag() == "Blob ball")
					{
						physicsScene->RemoveObject(var);
					}
				}
				std::vector<Constraint*> constraints = physicsScene->GetConstraints();
				for each (Constraint* var in constraints)
				{
					physicsScene->RemoveConstraint(var);
				}
			}//If it is the blob delete it and all of its constraints
			else {
				physicsScene->RemoveObject(physicsScene->GetObjectAt(deleteCount));
			}
		}

	}
	 //Will start spawning o0bjects across a grid
	if (input->wasKeyPressed(aie::INPUT_KEY_BACKSPACE)) {
		PhysicsObject* obj = new PhysicsObject(glm::vec3(spawnAcross, 5.0f, 1.0f), 1.0f, glm::vec3(1.0f), 1.0f,true);
		physicsScene->AttachObject(obj);
		obj->SetCollider(new SphereCollider(0.3f));
		obj->SetLifeTime(5.0f, true);
		spawnAcross++;
	}
	//Shoot balls from the camera
	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT)) {
		PhysicsObject* obj = new PhysicsObject(true,2.0f);//enabling physics
		obj->SetPosition(m_camera->GetPosition());
		obj->SetVelocity(m_camera->GetFront() * 20.0f);
		obj->SetCollider(new SphereCollider(0.5f));
		obj->SetTag("Shotball");
		physicsScene->AttachObject(obj);
	}
	//Apply force to the Marbles
	if (input->wasKeyPressed(aie::INPUT_KEY_LEFT_SHIFT))
	{
		for each (PhysicsObject* var in physicsScene->GetObjects())
		{
			if (var->GetTag() == "Marble")
			{
				var->ApplyForce(glm::vec3(2000, 0, 0));
			}
		}
	}

	//Create Objects
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
				obj->SetCollider(new AABBCollider(glm::vec3(0.3f)));
			else
				obj->SetCollider(new SphereCollider(0.3f));
			physicsScene->AttachObject(obj);
		}
		else {
			PhysicsObject *obj = new PhysicsObject(gravityObject, lifetimeObject);
			obj->SetPosition(glm::vec3(positionObject[0], positionObject[1], positionObject[2]));
			if (selection == 1)
				obj->SetCollider(new AABBCollider(glm::vec3(0.3f)));
			else
				obj->SetCollider(new SphereCollider(0.3f));
			physicsScene->AttachObject(obj);

		}
	}
	ImGui::End();

	//Physics Demo Operations
	ImGui::Begin("Demos - 6 Second Lifetime");
	if (ImGui::Button("AABB vs Sphere"))
	{
		PhysicsObject *obj = new PhysicsObject(true,6.0f);
		obj->SetPosition(glm::vec3(5.0f,5.0f,0.0f));
		obj->SetCollider(new SphereCollider(0.3f));
		physicsScene->AttachObject(obj);
	}
	if (ImGui::Button("AABB vs AABB"))
	{
		PhysicsObject *obj = new PhysicsObject(true, 6.0f);
		obj->SetPosition(glm::vec3(8.0f, 5.0f, 0.0f));
		obj->SetCollider(new AABBCollider(glm::vec3(0.3f)));
		physicsScene->AttachObject(obj);
	}
	ImGui::End();

	m_camera->Update(0.016f);//Passing in delta time no need for physics as if we drag window time between frames will be massive and cause everything to fling around
	physicsScene->AddForceToAllobjects(glm::vec3(0, -9.8f, 0));
	physicsScene->Update(0.016f);//Passing in delta time no need for physics as if we drag window time between frames will be massive and cause everything to fling around
	
	//ImGui::Begin("Object Manipulator");
	//ImGui::Checkbox("Mouse to Drag Objects", &affectObjects);
	//if (affectObjects){
	//	for each (PhysicsObject* var in physicsScene->GetObjects())
	//	{
	//		if ((int)m_camera->mouse_click_callback(input->getMouseX(), input->getMouseY()).x == (int)(var->GetPosition().x))
	//		{
	//			var->SetPosition(m_camera->mouse_click_callback(input->getMouseX(), input->getMouseY()));
	//		}
	//	}
	//}
	//ImGui::End();
	double currentTime = glfwGetTime();
	nbFrames++;
	if (currentTime - lastTime >= 1.0)
	{
		std::cout << "FPS - " << nbFrames << std::endl;
		nbFrames = 0;
		lastTime += 1.0;
	}
}

void Physics_Walkthrough_App::draw()
{
	// wipe the screen to the background colour
	clearScreen();
	// wipe the gizmos clean for this frame
	aie::Gizmos::clear();
	RenderGizmosGrid();
	physicsRenderer->Draw(physicsScene);//Use the phys renderer to draw the phys objects
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
