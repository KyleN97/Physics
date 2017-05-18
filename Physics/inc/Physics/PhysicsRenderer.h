#pragma once
#include "Physics\PhysicsScene.h"

class PhysicsRenderer
{
public:
	PhysicsRenderer();
	~PhysicsRenderer();
	void Draw(PhysicsScene* scene);
};

