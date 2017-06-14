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
	int spawnAcross = 0;
	int deleteCount = 0;
	float positionObject[3] = { 0 };
	float lifetimeObject = 0.0f;
	bool gravityObject = false;
	bool affectObjects = false;
	// camera transforms
	Camera *m_camera = nullptr;
	PhysicsScene* physicsScene;
	PhysicsRenderer* physicsRenderer;
};