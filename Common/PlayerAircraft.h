#pragma once
#include "Aircraft.hpp"
#include <string>
#include "CommandQueue.h"
#include <map>

class PlayerAircraft :
	public Aircraft
{
public:
	enum Action
	{
		MoveUp,
		MoveDown,
		MoveRight,
		MoveLeft
	};

	PlayerAircraft(Game* game, States::ID id);

private:
	void updateCurrent(const GameTimer& gt) override;
	unsigned int getCategory() override;
	bool isRealtimeAction(Action action);

	std::map<int, Action> mKeyBinding;
	std::map<Action, Command> mActionBinding;

	float playerSpeed = 1.0f;

public:
	void handleEvent(CommandQueue& commands);
	void handleRealtimeInput(CommandQueue& commands);
	void assignKey(Action action, int key);
	int getAssignedKey(Action action) const;
	void SetPlayerSpeed(float speed);
};

struct AircraftMover
{
	AircraftMover(float vx, float vy, float vz) :
		velocity(vx, vy, vz)
	{
	}

	void operator()(SceneNode& node, const GameTimer& gt) const
	{
		auto& aircraft = static_cast<PlayerAircraft&>(node);
		aircraft.setVelocity(velocity);
	}

	XMFLOAT3 velocity;
};
