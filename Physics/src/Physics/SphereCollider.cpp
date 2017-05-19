#include "Physics\SphereCollider.h"
#include "Physics\PhysicsObject.h"


SphereCollider::SphereCollider(float _radius) : radius(_radius), Collider(Type::SPHERE)
{

}

SphereCollider::SphereCollider() : radius(1.0f), Collider(Type::SPHERE)
{

}
bool SphereCollider::Intersects(Collider * other) const
{
	switch (other->GetType())
	{
	case Type::SPHERE:
		return SphereToSphereIntersect(this, (SphereCollider*)other);
	}
}

void SphereCollider::Transform(PhysicsObject * object)
{
	SetPosition(object->GetPosition());
}
