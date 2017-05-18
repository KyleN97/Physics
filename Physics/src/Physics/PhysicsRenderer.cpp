#include "Physics\PhysicsRenderer.h"
#include <Gizmos.h>

PhysicsRenderer::PhysicsRenderer()
{
}


PhysicsRenderer::~PhysicsRenderer()
{
}

void PhysicsRenderer::Draw(PhysicsScene * scene)
{
	for each (PhysicsObject* var in scene->GetObjects())
	{
		aie::Gizmos::addSphere(var->GetPosition(), 0.5f, 16, 16, glm::vec4(0, 0, 1, 1));
	}
}
