/*
* Name: Gastello, Andrii
* Date: 01.28.2023
* Last Modified: 04.10.2023
*/
#pragma once
#include "SceneNode.hpp"

class Entity :
	public SceneNode
{
public:
	Entity(Game* game, States::ID id);
	void setVelocity(XMFLOAT3 velocity);
	void setVelocity(float vx, float vy, float vz);
	XMFLOAT3 getVelocity() const;

	void updateCurrent(const GameTimer& gt) override;

public:
	XMFLOAT3 mVelocity;
};
