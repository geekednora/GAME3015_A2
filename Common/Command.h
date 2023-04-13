#pragma once


#include <functional>
#include <cassert>
#include "GameTimer.h"
#include "Category.h"

class SceneNode;

struct Command
{
	Command();

	std::function<void(SceneNode&, const GameTimer&)> action;
	unsigned int category;
};

template <typename GameObject, typename Function>
std::function<void(SceneNode&, const GameTimer&)> derivedAction(Function fn)
{
	return [=](SceneNode& node, const GameTimer& dt)
	{
		// Check if cast is safe
		assert(dynamic_cast<GameObject*>(&node) != nullptr);

		// Downcast node and invoke function on it
		fn(static_cast<GameObject&>(node), dt);
	};
}
