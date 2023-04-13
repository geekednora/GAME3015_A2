#pragma once
#include "Entity.hpp"

class SpriteNode :
	public Entity
{
public:
	SpriteNode(Game* game, States::ID id);

protected:
	XMFLOAT3 mTiling;
	void drawCurrent() const override;
	void buildCurrent() override;
};
