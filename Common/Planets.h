#pragma once
#include "SpriteNode.h"
#include <string>

class Planets
	: public SpriteNode
{
public:
	Planets(Game* game, States::ID id);

private:
	void updateCurrent(const GameTimer& gt) override;
	void drawCurrent() const override;
	float mScrollSpeed;
	std::string PlanetsNames[10] = {
		"Planet", "Planet02", "Planet03", "Planet04", "Planet05", "Planet06", "Planet07", "Planet08", "Planet09",
		"Planet10"
	};
};
