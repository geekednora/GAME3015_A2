#pragma once
#include "GameState.h"
#include "Game.hpp"


GameState::GameState(StateStack& stack, Context context)
	: State(stack, context),
	  mGame(context.mGame)
	  , mSceneGraph(new SceneNode(context.mGame, mState))
	  , mState(States::Game)
	  , IsPaused(false)
	  , mWorldBounds(-1.5f, 1.5f, 200.0f, 0.0f) //Left, Right, Down, Up
	  , mBackground(nullptr)
{
}

void GameState::draw()
{
	mSceneGraph->draw();
}

bool GameState::update(const GameTimer& dt)
{
	if (!IsSatesPlaying())
	{
		return true;
	}
	if (GetAsyncKeyState('P') & 0x8000 && !IsPaused)
	{
		mGame->PushCurrentRenderState(States::Pause);
		IsPaused = true;
	}
	else if (GetAsyncKeyState(' ') & 0x8000 && IsPaused)
	{
		mGame->PopCurrentRenderState();
		IsPaused = false;
	}
	if (IsPaused)
	{
		if (GetAsyncKeyState('M') & 0x8000)
		{
			mGame->PopCurrentRenderState();
			mGame->PopCurrentRenderState();
			mGame->PushCurrentRenderState(States::Menu);
			IsPaused = false;
		}
		return true;
	}
	mPlayerAircraft->setVelocity(0.f, 0.f, 0.f);
	processInput();
	while (!mCommandQueue.isEmpty())
		mSceneGraph->onCommand(mCommandQueue.pop(), dt);
	mSceneGraph->update(dt);
	return true;
}

bool GameState::IsSatesPlaying()
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

bool GameState::handleEvent(Command& event)
{
	// If any key is pressed, trigger the next screen


	return true;
}

void GameState::buildState()
{
#pragma region Player
	std::unique_ptr<PlayerAircraft> player(new PlayerAircraft(mGame, mState));
	mPlayerAircraft = player.get();
	mPlayerAircraft->setPosition(-2, 0.1, 0.0);
	mPlayerAircraft->setScale(1.0, 1.0, 1.0);
	mSceneGraph->attachChild(std::move(player));
#pragma endregion
#pragma region Enemies
	std::unique_ptr<EnemyAircraft> enemy1(new EnemyAircraft(mGame, mState));
	auto raptor = enemy1.get();
	raptor->setPosition(rand() % 10 + 6, 0.05, 1.7 - rand() % 3);
	raptor->setScale(1.0, 1.0, 1.0);
	raptor->setWorldRotation(0, XM_PI * 2, 0);
	mSceneGraph->attachChild(std::move(enemy1));
	mEnemies.push_back(raptor);
	std::unique_ptr<EnemyAircraft> enemy2(new EnemyAircraft(mGame, mState));
	auto raptor2 = enemy2.get();
	raptor2->setPosition(rand() % 10 + 6, 0.05, 1.7 - rand() % 3);
	raptor2->setScale(1.0, 1.0, 1.0);
	raptor2->setWorldRotation(0, XM_PI * 2, 0);
	mSceneGraph->attachChild(std::move(enemy2));
	mEnemies.push_back(raptor2);
#pragma endregion
#pragma region Scenery
	std::unique_ptr<Background> backgroundSprite(new Background(mGame, mState));
	mBackground = backgroundSprite.get();
	//mBackground->setPosition(mWorldBounds.x, mWorldBounds.z);
	mBackground->setPosition(5.0, 0, 0.0);
	mBackground->setScale(20.0, 1.0, 20.0);
	mSceneGraph->attachChild(std::move(backgroundSprite));
	std::unique_ptr<Planets> planetsSprite1(new Planets(mGame, mState));
	auto Planet1 = planetsSprite1.get();
	//mBackground->setPosition(mWorldBounds.x, mWorldBounds.z);
	Planet1->setPosition(rand() % 10 + 6, 0.05, 1.7 - rand() % 3);
	Planet1->setScale(1.0, 1.0, 1.0);
	mSceneGraph->attachChild(std::move(planetsSprite1));
	mPlanets.push_back(Planet1);
	std::unique_ptr<Planets> planetsSprite2(new Planets(mGame, mState));
	auto Planet2 = planetsSprite2.get();
	//mBackground->setPosition(mWorldBounds.x, mWorldBounds.z);
	Planet2->setPosition(rand() % 10 + 6, 0.05, 1.7 - rand() % 3);
	Planet2->setScale(1.0, 1.0, 1.0);
	mSceneGraph->attachChild(std::move(planetsSprite2));
	mPlanets.push_back(Planet2);
#pragma endregion
	mSceneGraph->build();
}

CommandQueue& GameState::getCommandQueue()
{
	return mCommandQueue;
}

void GameState::processInput()
{
	CommandQueue& commands = getCommandQueue();
	mPlayerAircraft->handleEvent(commands);
	mPlayerAircraft->handleRealtimeInput(commands);
}
#pragma endregion
