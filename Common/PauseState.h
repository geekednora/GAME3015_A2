#pragma once
#include "State.h"
#include "StateStack.h"
#include "Background.h"
#include "SceneNode.hpp"
#include "SpriteNode.h"
#include "Label.h"


class PauseState : public State
{
public:
	PauseState(StateStack& stack, Context context);

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
	Label* mLabel;

	// Inherited via State
};
