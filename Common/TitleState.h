#pragma once
#include "State.h"
#include "StateStack.h"
#include "Background.h"
#include "SceneNode.hpp"
#include "SpriteNode.h"
#include "Background.h"
#include "Label.h"


class TitleState : public State
{
public:
	TitleState(StateStack& stack, Context context);

	void buildState() override;
	void draw() override;
	bool update(const GameTimer& dt) override;
	bool handleEvent(Command& event) override;

private:
	bool IsSatesPlaying();

	enum Layer
	{
		BACKGROUND,
		AIR,
		LAYER_COUNT
	};

	Game* mGame;
	States::ID mState;
	SceneNode* mSceneGraph;
	std::array<SceneNode*, LAYER_COUNT> mSceneLayers;

	XMFLOAT4 mWorldBounds;
	Background* mBackground;
	Label* mLabel;

	// Inherited via State
};
