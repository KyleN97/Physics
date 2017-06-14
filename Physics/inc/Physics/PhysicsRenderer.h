#pragma once
#include "Physics\PhysicsScene.h"

class PhysicsRenderer
{
public:
	PhysicsRenderer() {};
	~PhysicsRenderer() {};
	void Draw(PhysicsScene* scene);//Draw the scene
	const glm::vec4& GetRenderColor() const {return renderColor;}
	void SetRenderColor(const glm::vec4& color) { renderColor = color; }
protected:
	glm::vec4 renderColor = glm::vec4(0.0f,0.0f,1.0f,1.0f);//Used to colour the objects and show collisions

};

