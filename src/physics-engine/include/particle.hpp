#pragma once

#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "core.hpp"
#include <assert.h>

class Particle
{
protected:
	//Holds the position of the particle in world space
	Vector2 position;

	//Holds the linear velocity of the particle in world space
	Vector2 velocity;

	//Holds the acceleration of the particle
	Vector2 acceleration;

	float damping;
	float inverseMass;

public:
	void Particle::setDamping(const float value)
	{
		damping = value;
	}

	float Particle::getDamping() const
	{
		return damping;
	}

	void Particle::setAcceleration(const Vector2& value)
	{
		acceleration = value;
	}

	void Particle::setAcceleration(const float x, const float y)
	{
		acceleration.x = x;
		acceleration.y = y;
	}

	void setMass(const float value)
	{
		inverseMass = 1.0f / value;
	}

	void setInverseMass(const float value)
	{
		inverseMass = value;
	}

	void setPosition(const Vector2& value)
	{
		position = value;
	}

	void setPosition(const float x, const float y)
	{
		position.x = x;
		position.y = y;
	}

	void Particle::getPosition(Vector2* positionPtr) const
	{
		*positionPtr = position;
	}

	Vector2 Particle::getPosition() const
	{
		return position;
	}

	void integrate(float deltaTime)
	{
		//Skip integration objects with infinite mass
		if (inverseMass <= 0.0f)
			return;

		assert(deltaTime > 0.0f);

		//Update position
		position.addScaledVector(velocity, deltaTime);
		Vector2 resultingAcceleration = acceleration;

		//Update velocity
		velocity.addScaledVector(resultingAcceleration, deltaTime);
		
		//Impose drag
		velocity *= powf(damping, deltaTime);
	}


};
#endif