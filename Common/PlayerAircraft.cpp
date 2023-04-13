#include "PlayerAircraft.h"

PlayerAircraft::PlayerAircraft(Game* game, States::ID id) : Aircraft(game, id)
{
	mSprite = "Player";
	mKeyBinding['W'] = MoveUp;
	mKeyBinding['S'] = MoveDown;
	mKeyBinding['D'] = MoveRight;
	mKeyBinding['A'] = MoveLeft;

	Command command;

	command.action = derivedAction<Aircraft>(AircraftMover(0.0f, 0.f, playerSpeed));
	command.category = getCategory();
	mActionBinding[MoveUp] = command;

	command.action = derivedAction<Aircraft>(AircraftMover(0.0f, 0.f, -playerSpeed));
	mActionBinding[MoveDown] = command;

	command.action = derivedAction<Aircraft>(AircraftMover(playerSpeed, 0.f, 0.f));
	mActionBinding[MoveRight] = command;

	command.action = derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.f, 0.f));
	mActionBinding[MoveLeft] = command;
}

void PlayerAircraft::updateCurrent(const GameTimer& gt)
{
	Entity::updateCurrent(gt);
}

unsigned int PlayerAircraft::getCategory()
{
	return Category::PlayerAircraft;
}

bool PlayerAircraft::isRealtimeAction(Action action)
{
	if (mActionBinding[action].action)
	{
		return true;
	}
	return false;
}

void PlayerAircraft::handleEvent(CommandQueue& commands)
{
	// stuff
}

void PlayerAircraft::handleRealtimeInput(CommandQueue& commands)
{
	for each (auto pair in mKeyBinding)
	{
		if (GetAsyncKeyState(pair.first) & 0x8000 && isRealtimeAction(pair.second))
		{
			commands.push(mActionBinding[pair.second]);
		}
	}
}

void PlayerAircraft::assignKey(Action action, int key)
{
	//mKeyBinding.emplace(action, key);
}

int PlayerAircraft::getAssignedKey(Action action) const
{
	// help pls
	return 0;
}

void PlayerAircraft::SetPlayerSpeed(float speed)
{
	playerSpeed = speed;
}
