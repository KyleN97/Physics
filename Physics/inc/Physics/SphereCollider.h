#pragma once
#include "Physics\Collider.h"
#include <glm\vec3.hpp>
class PhysicsObject;
class SphereCollider : public Collider
{
public:
	SphereCollider(float _radius) : radius(_radius), Collider(Type::SPHERE){}
	SphereCollider() : radius(1.0f), Collider(Type::SPHERE){}
	virtual ~SphereCollider() {};

	const glm::vec3 &GetPosition() const { return position; }
	const float GetRadius() const { return radius; }

	void SetPosition(const glm::vec3 & _position) { position = _position; }
	void SetRadius(float _radius) { radius = _radius; }

	bool Intersects(Collider* other,IntersectData* intersect) const;//Intersecting
	virtual void Transform(PhysicsObject* object);
protected:
	glm::vec3 position;
	float radius;

};

