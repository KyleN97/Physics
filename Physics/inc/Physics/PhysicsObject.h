#pragma once
#include <glm\glm.hpp>
class PhysicsObject
{
public:
	PhysicsObject();
	~PhysicsObject();

	void Update(float deltaTime);

	void ApplyForce(glm::vec3 force);//Apply force to an object with a certain force
	
	const glm::vec3 GetPosition()		const { return position;}//Get position of the object
	const glm::vec3 GetVelocity()		const { return velocity;}//Get the velocity of the object
	const glm::vec3 GetAcceleration()	const { return acceleration; }//Get the acceleration of the object
	const float GetMass()				const { return mass; }//Get the mass of the object
	const float GetFriction()			const { return friction; }//Get the friction of the object

	void SetPosition(const glm::vec3& value)	 { position = value;}//Set the positon of the object
	void SetVelocity(const glm::vec3& value)	 { velocity = value;}//Set the velocity of the object...(Should not be used directly
	//if you want to change the velocity you should add a force of some sort.
	void SetAcceleration(const glm::vec3& value) { acceleration = value;}//Set the acceleration for the object.
	void SetMass(const float& value)			 { mass = value;}//Set the mass of the object
	void SetFriction(const float& value)		 { friction = value;}//Set the friction of the object

protected:
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	float mass;
	float friction;
	//Default member variables for basic physics
};

