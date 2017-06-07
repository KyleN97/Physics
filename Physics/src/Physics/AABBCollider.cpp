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

bool AABBCollider::Intersects(Collider * other,IntersectData* intersect) const
{
	switch (other->GetType())
	{
		case Type::AABB:
			return AABBTOAABBIntersect(this, (AABBCollider*)other,intersect);
			break;
		case Type::SPHERE:
			return SphereToAABBIntersect((SphereCollider*)other, this, intersect);
		default:
			return false;
	}
}

void AABBCollider::Transform(PhysicsObject * object)
{
	SetPosition(object->GetPosition());
}
