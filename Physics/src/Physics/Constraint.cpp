#include "Physics\Constraint.h"
#include "Physics\PhysicsObject.h"


Constraint::Constraint()
{
}

Constraint::Constraint(std::vector<PhysicsObject*>& _objects, Type _type) : objects(_objects),type(_type)
{
}


Constraint::~Constraint()
{
}
