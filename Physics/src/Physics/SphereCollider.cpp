#include "Physics\SphereCollider.h"
#include "Physics\PhysicsObject.h"


bool SphereCollider::Intersects(Collider * other, IntersectData* intersect) const
{
	switch (other->GetType())
	{
	case Type::SPHERE:
		return SphereToSphereIntersect(this, (SphereCollider*)other, intersect);
		break;
	case Type::AABB:
		return SphereToAABBIntersect(this,(AABBCollider*)other, intersect);
		break;
	default:
		return false;
	}//Determine what type of collider this is colliding with and execute the app. function
}

void SphereCollider::Transform(PhysicsObject * object)
{
	SetPosition(object->GetPosition());
}
