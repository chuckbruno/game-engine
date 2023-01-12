#pragma once

#ifndef PCONTACTGENERATOR_HPP
#define PCONTACTGENERATOR_HPP

#include "pcontact.hpp"

class ParticleContactGenerator
{
public:
	virtual unsigned addContact(ParticleContact* contact, unsigned limit) const = 0;
};


#endif