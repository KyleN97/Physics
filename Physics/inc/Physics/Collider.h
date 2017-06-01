#pragma once
class PhysicsObject;
class SphereCollider;
class AABBCollider;
class IntersectData;
class Collider
{
public:
	enum Type {
		NONE,
		SPHERE,
		AABB,
		OBB
	};
	Collider(Type _type);
	virtual ~Collider();
	Type GetType() const { return type; }
	virtual bool Intersects(Collider* other, IntersectData* intersect) const { return false; };
	static Collider* GetNullInstance();
	virtual void Transform(PhysicsObject* object) {};
	static bool SphereToSphereIntersect(const SphereCollider* sphere, const SphereCollider* other);
	static bool AABBTOAABBIntersect(const AABBCollider* aabb, const AABBCollider* other, IntersectData* intersect);
	static bool SphereToAABBIntersect(const SphereCollider* sphere, const AABBCollider* aabb,IntersectData* intersect);
	static bool SphereToSphereIntersect(const SphereCollider* sphere, const SphereCollider* other, IntersectData* intersect);
protected:
	Type type;
};


