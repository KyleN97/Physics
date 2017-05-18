#pragma once
#include <glm\glm.hpp>
class PhysicsObject
{
public:
	PhysicsObject();
	~PhysicsObject();

	void Update(float deltaTime);

	void ApplyForce(glm::vec3 force);//Apply force to an object with a certain force
	
	const glm::vec3 GetPosition() const {return position;}
	const glm::vec3 GetVelocity() const {return velocity;}
	const glm::vec3 GetAcceleration() const { return acceleration; }
	const float GetMass() const { return mass; }
	const float GetFriction() const { return friction; }

	void SetPosition(const glm::vec3& value) {position = value;}
	void SetVelocity(const glm::vec3& value) {velocity = value;}
	void SetAcceleration(const glm::vec3& value) {acceleration = value;}
	void SetMass(const float& value) {mass = value;}
	void SetFriction(const float& value) {friction = value;}


protected:
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	float mass;
	float friction;
};

