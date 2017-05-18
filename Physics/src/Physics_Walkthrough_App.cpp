#include "Physics_Walkthrough_App.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Camera.h"
#include "Physics\PhysicsObject.h"
#include "Physics\PhysicsScene.h"
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
	aie::Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	m_camera = new Camera();
	m_camera->SetProjection(glm::radians(45.0f), (float)getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.0f);
	m_camera->SetPosition(glm::vec3(10, 10, 10));
	m_camera->Lookat(glm::vec3(0, 0, 0));

	physicsScene = new PhysicsScene();
	physicsObjects.reserve(64);
	physicsObjects.push_back(new PhysicsObject(glm::vec3(3.0f),1.0f,glm::vec3(1.0f),1.0f));//Create a new phys object	
	physicsObjects.push_back(new PhysicsObject(glm::vec3(5.0f,5.0f,1.0f), 1.0f, glm::vec3(1.0f), 1.0f));//Create a new phys object
	physicsScene->AttachAllObjects(physicsObjects);
		//Set the position of the object aswell as the mass and accelation it will use
	return true;
}

void Physics_Walkthrough_App::shutdown()
{
	aie::Gizmos::destroy();
}

void Physics_Walkthrough_App::update(float deltaTime)
{
	m_camera->Update(deltaTime);
	physicsScene->Update(deltaTime);
	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
	if(input->isKeyDown(aie::INPUT_KEY_UP))
		physicsObjects[0]->ApplyForce(glm::vec3(3, 0, 0));//Apply a force to the object
	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
		physicsObjects[0]->ApplyForce(glm::vec3(0, 0, 3));//Apply a force to the object
	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
		physicsObjects[0]->ApplyForce(glm::vec3(-3, 0, 0));//Apply a force to the object
	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
		physicsObjects[0]->ApplyForce(glm::vec3(0, 0, -3));//Apply a force to the object
	if (input->isKeyDown(aie::INPUT_KEY_ENTER))
		physicsScene->RemoveObject(physicsObjects[1]);
}

void Physics_Walkthrough_App::draw()
{

	// wipe the screen to the background colour
	clearScreen();

	// wipe the gizmos clean for this frame
	aie::Gizmos::clear();
	RenderGizmosGrid();
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

	for each (PhysicsObject* var in physicsScene->GetObjects())
	{
		aie::Gizmos::addSphere(var->GetPosition(), 0.5f, 16, 16, glm::vec4(0, 0, 1, 1));		
	}
}