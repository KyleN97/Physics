#pragma once
#include "Physics\Collider.h"
#include <glm\vec3.hpp>
class PhysicsObject;
class AABBCollider : public Collider
{
public:
	AABBCollider() : size(1.0f), Collider(Type::AABB) {}
	AABBCollider(glm::vec3 _size) : size(_size), Collider(Type::AABB){}
	//Default constructors
	virtual ~AABBCollider() {};

	const glm::vec3 &GetPosition() const { return position; }
	const glm::vec3 &GetSize() const { return size; }

	void SetPosition(const glm::vec3 & _position) { position = _position; }
	void SetSize(const glm::vec3 & _size) { size = _size; }

	bool Intersects(Collider* other,IntersectData* intersect) const;//Is this AABB collider intersecting
	virtual void Transform(PhysicsObject* object);
protected:
	glm::vec3 position;
	glm::vec3 size;
};

