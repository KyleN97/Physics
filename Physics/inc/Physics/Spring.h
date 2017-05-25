#include "Physics\Constraint.h"
class Spring: public Constraint {

public:
	Spring(PhysicsObject* objA, PhysicsObject* objB);
	Spring(PhysicsObject* objA, PhysicsObject* objB,float _length,float _stiffness,float _friction);
	virtual ~Spring();
	void Update(float deltaTime);
protected:
	float length, stiffness, friction;
private:
};