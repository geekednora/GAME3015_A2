/*
* Name: Gastello, Andrii
* Date: 01.28.2023
* Last Modified: 04.10.2023
*/
#pragma once
#include "Entity.hpp"
#include <string>

class Aircraft :
	public Entity
{
public:

public:
	Aircraft(Game* game, States::ID id);

public:
	void buildCurrent() override;

protected:
};
