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

	physicsRenderer = new PhysicsRenderer();

	physicsScene = new PhysicsScene();
	physicsScene->AttachObject(new PhysicsObject(glm::vec3(0.0f,5.0f,0.0f),1.0f,glm::vec3(1.0f),1.0f,"Cube"));//Create a new phys object	
	physicsScene->GetObjectAt(0)->SetCollider(new AABBCollider(glm::vec3(0.3f,0.3f,0.3f)));
	physicsScene->AttachObject(new PhysicsObject(glm::vec3(0.0f,0.0f,0.0f), 1.0f, glm::vec3(1.0f), 1.0f,"Floor"));//Create a new phys object
	physicsScene->GetObjectAt(1)->SetCollider(new AABBCollider(glm::vec3(10.0f,1.0f,10.0f)));
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
