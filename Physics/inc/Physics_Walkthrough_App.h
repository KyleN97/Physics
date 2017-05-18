#pragma once

#include "Application.h"
#include <glm/mat4x4.hpp>
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
	// camera transforms
	Camera *m_camera = nullptr;
	PhysicsScene* physicsScene;
	PhysicsRenderer* physicsRenderer;
};