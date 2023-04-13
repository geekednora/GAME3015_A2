#pragma once
#include "Aircraft.hpp"
#include <string>

class EnemyAircraft :
	public Aircraft
{
public:
	EnemyAircraft(Game* game, States::ID id);

private:
	void updateCurrent(const GameTimer& gt) override;
	void drawCurrent() const override;

	float mEnemySpeed;
};
