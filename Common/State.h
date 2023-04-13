#pragma once
#include "StateIdentifiers.h"
#include "ResourceIdentifiers.h"

#include <memory>
#include "GameTimer.h"
#include "Command.h"

namespace sf
{
	class RenderWindow;
}

class StateStack;
class Player;
class Game;

class State
{
public:
	using Ptr = std::unique_ptr<State>;

	struct Context
	{
		Context(Game* game);

		Game* mGame;
	};

public:
	State(StateStack& stack, Context context);
	~State();

	virtual void buildState() = 0;
	virtual void draw() = 0;
	virtual bool update(const GameTimer& dt) = 0;
	virtual bool handleEvent(Command& event) = 0;

protected:
	void requestStackPush(States::ID stateID);
	void requestStackPop();
	void requestStateClear();

	Context getContext() const;

private:
	StateStack* mStack;
	Context mContext;
};

#pragma endregion
