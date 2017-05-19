#include "Physics\AABBCollider.h"
#include "Physics\PhysicsObject.h"


AABBCollider::AABBCollider() : size(1.0f), Collider(Type::AABB)
{

}

AABBCollider::AABBCollider(glm::vec3 _size) : size(_size), Collider(Type::AABB)
{

}


AABBCollider::~AABBCollider()
{
}

bool AABBCollider::Intersects(Collider * other) const
{
	switch (other->GetType())
	{
	case Type::AABB:
		return AABBTOAABBIntersect(this, (AABBCollider*)other);
	}
}

void AABBCollider::Transform(PhysicsObject * object)
{
	SetPosition(object->GetPosition());
}
