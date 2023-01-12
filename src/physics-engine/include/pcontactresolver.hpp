#pragma once

#ifndef PCONTACTRESOLVER_HPP
#define PCONTACTRESOLVER_HPP

#include "pcontact.hpp"

class ParticleContactResolver
{
protected:
	unsigned iterations;

	unsigned iterationsUsed;

public:
	ParticleContactResolver(unsigned iteration);
	
	void setIterations(unsigned iterations);

	void resolveContacts(ParticleContact* contactArray, unsigned numContacts, float duration);
};

#endif