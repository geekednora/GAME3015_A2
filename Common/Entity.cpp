/*
* Name: Gastello, Andrii
* Date: 01.28.2023
* Last Modified: 04.10.2023
*/
#include "Entity.hpp"

Entity::Entity(Game* game, States::ID id) : SceneNode(game, id), mVelocity(0, 0, 0)
{
}

void Entity::setVelocity(XMFLOAT3 velocity)
{
	mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy, float vz)
{
	mVelocity.x = vx;
	mVelocity.y = vy;
	mVelocity.z = vz;
}

XMFLOAT3 Entity::getVelocity() const
{
	return mVelocity;
}

void Entity::updateCurrent(const GameTimer& gt)
{
	XMFLOAT3 mV;
	mV.x = mVelocity.x * gt.DeltaTime();
	mV.y = mVelocity.y * gt.DeltaTime();
	mV.z = mVelocity.z * gt.DeltaTime();
	move(mV.x, mV.y, mV.z);

	renderer->World = getWorldTransform();
	renderer->NumFramesDirty++;
}
