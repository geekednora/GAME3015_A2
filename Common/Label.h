#pragma once
#include "SpriteNode.h"
#include <string>

class Label :
	public SceneNode
{
public:
	Label(Game* game, std::string labelName, States::ID id);
	void buildCurrent() override;

private:
	void updateCurrent(const GameTimer& gt) override;
	void drawCurrent() const override;
	float mScrollSpeed;
};
