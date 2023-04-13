#pragma once
#include "State.h"
#include "StateStack.h"
#include "Background.h"
#include "SceneNode.hpp"
#include "SpriteNode.h"
#include "Background.h"
#include "CommandQueue.h"
#include "PlayerAircraft.h"
#include "Planets.h"
#include "EnemyAircraft.h"


class GameState : public State
{
public:
	GameState(StateStack& stack, Context context);

	void buildState() override;
	void draw() override;
	bool update(const GameTimer& dt) override;
	bool handleEvent(Command& event) override;
	CommandQueue& getCommandQueue();
	void processInput();

private:
	bool IsSatesPlaying();

	enum Layer
	{
		BACKGROUND,
		AIR,
		LAYER_COUNT
	};

	Game* mGame;
	SceneNode* mSceneGraph;
	States::ID mState;
	bool IsPaused;
	std::array<SceneNode*, LAYER_COUNT> mSceneLayers;
	CommandQueue mCommandQueue;
	XMFLOAT4 mWorldBounds;
	XMFLOAT2 mSpawnPosition;
	PlayerAircraft* mPlayerAircraft;
	Background* mBackground;
	std::list<Planets*> mPlanets;
	std::list<EnemyAircraft*> mEnemies;
};
