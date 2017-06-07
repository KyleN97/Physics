#include "Physics\PhysicsRenderer.h"
#include <Gizmos.h>
#include "Physics\Collider.h"
#include "Physics\SphereCollider.h"
#include "Physics\AABBCollider.h"
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
		SetRenderColor(glm::vec4(0, 0, 0, 1));

		if (scene->isObjectColliding(var)) {
			SetRenderColor(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
		}
		switch (var->GetCollider()->GetType())
		{
			case Collider::Type::SPHERE:
				aie::Gizmos::addSphere(var->GetPosition(), ((SphereCollider*)var->GetCollider())->GetRadius(), 16, 16, GetRenderColor());
				break;
			case Collider::Type::AABB:
					aie::Gizmos::addAABBFilled(var->GetPosition(), ((AABBCollider*)var->GetCollider())->GetSize(), GetRenderColor());
				break;
			case Collider::Type::NONE:
				aie::Gizmos::addSphere(var->GetPosition(), 0.1f, 16, 16, glm::vec4(1,0,1,1));
				break;
		}
		for each (Constraint* var in scene->GetConstraints())
		{
			switch (var->GetType())
			{
			case Constraint::Type::SPRING:
				aie::Gizmos::addLine(var->GetObjects()[0]->GetPosition(), var->GetObjects()[1]->GetPosition(), glm::vec4(0, 0, 1, 1));
				aie::Gizmos::addLine(var->GetObjects()[0]->GetPosition(), var->GetObjects()[1]->GetPosition(), glm::vec4(0, 0, 1, 1));

			}
		}
	}
}
