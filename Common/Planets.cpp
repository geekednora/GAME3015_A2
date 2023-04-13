#include "Planets.h"
#include <time.h>


Planets::Planets(Game* game, States::ID id) : SpriteNode(game, id)
                                              , mScrollSpeed(1.0f)
{
	mSprite = PlanetsNames[rand() % PlanetsNames->length()];
	mTiling = XMFLOAT3(1.0f, 1.0f, 1.0f);
	setVelocity(-mScrollSpeed, 0, 0.0);
}

void Planets::updateCurrent(const GameTimer& gt)
{
	if (getWorldPosition().x <= -5.0)
	{
		srand(time(nullptr));
		setPosition(rand() % 10 + 6, 0.1, 1.7 - (rand() % 34) / 10);
		mSprite = PlanetsNames[rand() % PlanetsNames->length()];
		SpriteNode::drawCurrent();
	}
	Entity::updateCurrent(gt);
}

void Planets::drawCurrent() const
{
	SpriteNode::drawCurrent();
}
