#pragma once
#include "Physics\Collider.h"
#include <glm\glm.hpp>
class PhysicsObject;
class AABBCollider : public Collider
{
public:
	AABBCollider();
	AABBCollider(glm::vec3 size);
	virtual ~AABBCollider();
	const glm::vec3 &GetPosition() const { return position; }
	const glm::vec3 &GetSize() const { return size; }

	void SetPosition(const glm::vec3 & _position) { position = _position; }
	void SetSize(const glm::vec3 & _size) { size = _size; }

	bool Intersects(Collider* other) const;
	virtual void Transform(PhysicsObject* object);
protected:
	glm::vec3 position;
	glm::vec3 size;
};

