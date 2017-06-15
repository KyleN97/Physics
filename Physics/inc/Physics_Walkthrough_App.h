#pragma once
#include "Application.h"
#include <vector>
class Camera;
class PhysicsObject;
class PhysicsScene;
class PhysicsRenderer;
class Physics_Walkthrough_App : public aie::Application {
public:

	Physics_Walkthrough_App();
	virtual ~Physics_Walkthrough_App();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	void RenderGizmosGrid();
protected:
	int spawnAcross = 0;//Where to spawn items across the grid
	int deleteCount = 0;//The deletion count
	float positionObject[3] = { 0 };//Poisiton of object from GUI spawning
	float lifetimeObject = 0.0f;//lifetime of the GUI objects
	bool gravityObject = false;//gravity of the GUI objects
	bool affectObjects = false;//Used for mouse affecting objects
	// camera transforms
	Camera *m_camera = nullptr;
	PhysicsScene* physicsScene;
	PhysicsRenderer* physicsRenderer;
	//Frames per second debugging
	int nbFrames = 0;
	int lastTime = 0;
	//
};