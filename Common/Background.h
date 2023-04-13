#pragma once
#include "SpriteNode.h"
#include <string>

class Background :
	public SpriteNode
{
public:
	Background(Game* game, States::ID id);

private:
	void updateCurrent(const GameTimer& gt) override;
	void drawCurrent() const override;
	float mScrollSpeed;
};
