#include "TitleState.h"
#include "Game.hpp"


TitleState::TitleState(StateStack& stack, Context context)
	: State(stack, context),
	  mGame(context.mGame)
	  , mState(States::Title)
	  , mSceneGraph(new SceneNode(context.mGame, mState))
	  , mWorldBounds(-1.5f, 1.5f, 200.0f, 0.0f)
	  , mBackground(nullptr) //Left, Right, Down, Up
{
}

void TitleState::draw()
{
	mSceneGraph->draw();
}

bool TitleState::update(const GameTimer& dt)
{
	if (!IsSatesPlaying())
	{
		return true;
	}
	mSceneGraph->update(dt);
	if (GetAsyncKeyState(' ') & 0x8000)
	{
		mGame->PopCurrentRenderState();
		mGame->PushCurrentRenderState(States::Menu);
	}
	return true;
}

bool TitleState::handleEvent(Command& event)
{
	// If any key is pressed, trigger the next screen


	return true;
}

bool TitleState::IsSatesPlaying()
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

void TitleState::buildState()
{
#pragma region Scenery

	std::unique_ptr<Background> backgroundSprite(new Background(mGame, mState));
	mBackground = backgroundSprite.get();
	mBackground->setPosition(5.0, 0, 0.0);
	mBackground->setScale(20.0, 1.0, 20.0);
	mSceneGraph->attachChild(std::move(backgroundSprite));

	std::unique_ptr<Label> label(new Label(mGame, "TitleScreen", mState));
	mLabel = label.get();
	mLabel->setPosition(0.0, 1, 0.0);
	mLabel->setScale(4.0, 1.0, 2.0);
	mSceneGraph->attachChild(std::move(label));
#pragma endregion

	mSceneGraph->build();
}
#pragma endregion
