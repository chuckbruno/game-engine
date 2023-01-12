#include "include/pcontact.hpp"

void ParticleContact::resolve(float duration)
{
	resolveVelocity(duration);
	resolveInterpenetration(duration);
}

float ParticleContact::calculateSeparatingVelocity() const
{
	Vector2 relativeVelocity = particle[0]->getVelocity();
	if (particle[1])
		relativeVelocity -= particle[1]->getVelocity();
	return relativeVelocity * contactNormal;
}

void ParticleContact::resolveVelocity(float duration)
{
	float separatingVelocity = calculateSeparatingVelocity();

	// the contact is either separating or stationary so no impulse is required
	if (separatingVelocity > 0)
	{
		return;
	}

	//new separating velocity
	float newSepVelocity = -separatingVelocity * restitution;

	//take acceleration buildup into account (also solves resting contacts problem)
	Vector2 accCauseVelocity = particle[0]->getAcceleration();
	if (particle[1]) accCauseVelocity -= particle[1]->getAcceleration();
	float accCauseSepVelocity = accCauseVelocity * contactNormal * duration;

	//if we`re got a closing velocity due to acceleration buildup, remove it from the new separating velocity.
	if (accCauseSepVelocity < 0)
	{
		newSepVelocity += restitution * newSepVelocity;
		if (newSepVelocity < 0)
			newSepVelocity = 0;
	}

	float deltaVelocity = newSepVelocity - separatingVelocity;

	float totalInverseMass = particle[0]->getInverseMass();
	if (particle[1]) totalInverseMass += particle[1]->getInverseMass();

	//impulses have no effect if both objects have INFINITE mass
	if (totalInverseMass <= 0)return;

	float impulse = deltaVelocity / totalInverseMass;

	//impulse per unit of inverse mass
	Vector2 impulsePerIMass = contactNormal * impulse;

	//apply impulse
	particle[0]->setVelocity(particle[0]->getVelocity() + impulsePerIMass * particle[0]->getInverseMass());
	if (particle[1])
	{
		//Second object goes in the opposite direction
		particle[1]->setVelocity(particle[1]->getVelocity() + impulsePerIMass * -particle[1]->getInverseMass());
	}
}

void ParticleContact::resolveInterpenetration(float duration)
{
	//if objects don't penetrate, skip this step
	if (penetration <= 0)return;
	float totalInverseMass = particle[0]->getInverseMass();
	if (particle[1])
		totalInverseMass += particle[1]->getInverseMass();

	//if both objects have INFINITE mass, THEN we do nothing
	if (totalInverseMass <= 0) return;

	//movement per unit of inverse mass.
	Vector2 movePerIMass = contactNormal * (penetration / totalInverseMass);

	//calculate movement per object
	particleMovement[0] = movePerIMass * particle[0]->getInverseMass();

	if (particle[1])
	{
		particleMovement[1] = movePerIMass * -particle[1]->getInverseMass();
	}
	else
	{
		particleMovement[1].clear();
	}

	//apply the movement
	particle[0]->setPosition(particle[0]->getPosition() + particleMovement[0]);

	if (particle[1])
	{
		particle[1]->setPosition(particle[1]->getPosition() + particleMovement[1]);
	}

}	
