#include "Background.h"

Background::Background(Game* game, States::ID id): SpriteNode(game, id)
                                                   , mScrollSpeed(1.0f)
{
	mSprite = "Background";
	mTiling = XMFLOAT3(10.0f, 10.0f, 10.0f);
	setVelocity(-mScrollSpeed, 0, 0.0);
}

void Background::updateCurrent(const GameTimer& gt)
{
	if (getWorldPosition().x <= -5.0)
	{
		setPosition(5.0, 0, 0.0);
	}
	Entity::updateCurrent(gt);
}

void Background::drawCurrent() const
{
}
