#include "MainMenuState.h"
#include "Game.hpp"


MainMenuState::MainMenuState(StateStack& stack, Context context)
	: State(stack, context),
	  mGame(context.mGame)
	  , mSceneGraph(new SceneNode(context.mGame, mState))
	  , mState(States::Menu)
	  , mWorldBounds(-1.5f, 1.5f, 200.0f, 0.0f)
	  , mBackground(nullptr) //Left, Right, Down, Up
{
}

void MainMenuState::draw()
{
	mSceneGraph->draw();
}

bool MainMenuState::update(const GameTimer& dt)
{
	if (!IsSatesPlaying())
	{
		return true;
	}
	mSceneGraph->update(dt);
	if (GetAsyncKeyState('1') & 0x8000)
	{
		mGame->PopCurrentRenderState();
		mGame->PushCurrentRenderState(States::Game);
	}
	if (GetAsyncKeyState('2') & 0x8000)
	{
		//close
	}
	return true;
}

bool MainMenuState::IsSatesPlaying()
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

bool MainMenuState::handleEvent(Command& event)
{
	// If any key is pressed, trigger the next screen


	return true;
}

void MainMenuState::buildState()
{
#pragma region Scenery

	std::unique_ptr<Background> backgroundSprite(new Background(mGame, mState));
	mBackground = backgroundSprite.get();
	mBackground->setPosition(5.0, 0, 0.0);
	mBackground->setScale(20.0, 1.0, 20.0);
	mSceneGraph->attachChild(std::move(backgroundSprite));

	std::unique_ptr<Label> label3(new Label(mGame, "Logo", mState));
	mLogoLabel = label3.get();
	mLogoLabel->setPosition(0.0, 1, 1);
	mLogoLabel->setScale(3.0f, 1.0, 0.5);
	mSceneGraph->attachChild(std::move(label3));

	std::unique_ptr<Label> label(new Label(mGame, "Play", mState));
	mPlayLabel = label.get();
	mPlayLabel->setPosition(0.0, 1, 0);
	mPlayLabel->setScale(1, 1.0, 0.5);
	mSceneGraph->attachChild(std::move(label));

	std::unique_ptr<Label> label2(new Label(mGame, "Exit", mState));
	mExitLabel = label2.get();
	mExitLabel->setPosition(0.0, 1, -0.7);
	mExitLabel->setScale(1.0f, 1.0, 0.5);
	mSceneGraph->attachChild(std::move(label2));
#pragma endregion

	mSceneGraph->build();
}
#pragma endregion
