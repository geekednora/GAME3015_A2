#include "PauseState.h"
#include "Game.hpp"


PauseState::PauseState(StateStack& stack, Context context)
	: State(stack, context),
	  mGame(context.mGame)
	  , mState(States::Pause)
	  , mSceneGraph(new SceneNode(context.mGame, mState))
{
}

void PauseState::draw()
{
	mSceneGraph->draw();
}

bool PauseState::update(const GameTimer& dt)
{
	return true;
}

bool PauseState::handleEvent(Command& event)
{
	// If any key is pressed, trigger the next screen


	return true;
}

bool PauseState::IsSatesPlaying()
{
	for (int i = 0; i < mGame->GetCurrentState().size(); i++)
	{
		if (mGame->GetCurrentState()[i] == mState)
		{
			return true;
		}
	}
	return false;
}

void PauseState::buildState()
{
#pragma region Scenery

	std::unique_ptr<Label> label(new Label(mGame, "Pause", mState));
	mLabel = label.get();
	mLabel->setPosition(0.0, 1, 0.0);
	mLabel->setScale(4.0, 1.0, 2.0);
	mSceneGraph->attachChild(std::move(label));
#pragma endregion

	mSceneGraph->build();
}
#pragma endregion
