#pragma once

#include "Application.h"
#include <glm/mat4x4.hpp>
#include <vector>
class Camera;
class PhysicsObject;
class PhysicsScene;
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

	// camera transforms
	Camera *m_camera = nullptr;
	PhysicsScene* physicsScene;
	std::vector<PhysicsObject*> physicsObjects;
};