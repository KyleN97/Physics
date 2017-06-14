#include "Physics\AABBCollider.h"
#include "Physics\PhysicsObject.h"

bool AABBCollider::Intersects(Collider * other,IntersectData* intersect) const
{
	switch (other->GetType())//Determine what type of collider this is colliding with and execute the app. function
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

void AABBCollider::Transform(PhysicsObject * object)//Change the transform
{
	SetPosition(object->GetPosition());
}
