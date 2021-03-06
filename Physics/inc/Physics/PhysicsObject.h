#pragma once
#include <glm\vec3.hpp>
#include <glm\geometric.hpp>
#include <string>
class Collider;
class PhysicsObject
{
public:
	PhysicsObject(bool _isPhysicsEnabled) {
		this->SetIsPhysicsEnabled(_isPhysicsEnabled);
	}
	PhysicsObject(bool _isPhysicsEnabled,float _lifetime) {
		this->SetIsPhysicsEnabled(_isPhysicsEnabled);
		this->SetLifeTime(_lifetime,true);
	}
	PhysicsObject(glm::vec3 _position, float _mass, glm::vec3 _acceleration, float _friction) {
		this->SetPosition(glm::vec3(_position));
		this->SetMass(_mass);
		this->SetAcceleration(_acceleration);
		this->SetFriction(_friction);
	}
	PhysicsObject(glm::vec3 _position, float _mass, glm::vec3 _acceleration, float _friction,bool _isPhysicsEnabled) {
		this->SetPosition(glm::vec3(_position));
		this->SetMass(_mass);
		this->SetAcceleration(_acceleration);
		this->SetFriction(_friction);
		this->SetIsPhysicsEnabled(_isPhysicsEnabled);
	}
	PhysicsObject(glm::vec3 _position, float _mass, glm::vec3 _acceleration, float _friction,std::string _tag) {
		this->SetPosition(glm::vec3(_position));
		this->SetMass(_mass);
		this->SetAcceleration(_acceleration);
		this->SetFriction(_friction);
		this->SetTag(_tag);
	}
	PhysicsObject(glm::vec3 _position, float _mass, glm::vec3 _acceleration, float _friction, std::string _tag,bool _isPhysicsEnabled) {
		this->SetPosition(glm::vec3(_position));
		this->SetMass(_mass);
		this->SetAcceleration(_acceleration);
		this->SetFriction(_friction);
		this->SetTag(_tag);
		this->SetIsPhysicsEnabled(_isPhysicsEnabled);
	}
	
	PhysicsObject() {};
	~PhysicsObject();

	void Update(float deltaTime);
	void ApplyForce(glm::vec3 force);//Apply force to an object with a certain force
	void SetPosition(const glm::vec3& value) { position = value; }//Set the positon of the object
	void SetVelocity(const glm::vec3& value) { velocity = value; }//Set the velocity of the object...(Should not be used directly if you want to change the velocity you should add a force of some sort).
	void SetAcceleration(const glm::vec3& value) { acceleration = value; }//Set the acceleration for the object.
	void SetMass(float value) { mass = value; }//Set the mass of the object
	void SetFriction(float value) { friction = value; }//Set the friction of the object
	void SetCollider(Collider* _collider);//Set the current Phys objects collider
	void SetTag(std::string _tag) { tag = _tag; }
	void SetIsPhysicsEnabled(bool _isPhysicsEnabled) { isPhysicsEnabled = _isPhysicsEnabled; }
	void SetLifeTime(float _lifetime, bool _hasLifeTime) { lifetime = _lifetime; hasLifeTime = _hasLifeTime; }

	const glm::vec3& GetPosition()		const { return position; }//Get position of the object
	const glm::vec3& GetVelocity()		const { return velocity; }//Get the velocity of the object
	const glm::vec3& GetAcceleration()	const { return acceleration; }//Get the acceleration of the object
	const std::string& GetTag()			const { return tag; }
	float GetRemainingLifetime()		const { return lifetime; }
	float GetMass()						const { return mass; }//Get the mass of the object
	float GetFriction()					const { return friction; }//Get the friction of the object
	bool GetIsPhysicsEnabled()			const { return isPhysicsEnabled; }
	bool GetLifetime()					const { return hasLifeTime; }


	Collider* GetCollider();//Get the current collider attatched to the current Phys object.

protected:
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	float mass = 1.0f;
	float friction = 1.0f;
	Collider* collider = nullptr;
	std::string tag = "null";
	bool isPhysicsEnabled = false;
	float lifetime = 5.0f;
	bool hasLifeTime = false;
	//Default member variables for basic physics
};

