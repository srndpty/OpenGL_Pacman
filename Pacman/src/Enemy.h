// Enemy.h
// “G‚ð•\Œ»‚·‚éƒNƒ‰ƒX

#pragma once

#include "Character.h"

class Enemy : public Character
{
public:
	static constexpr Vec2i SHEET_COUNT = { 2, 4 };
	static constexpr int ANIM_INTERVAL = 8;
	static constexpr float MOVE_SPEED = 0.002f;

public:
	Enemy(Field& field);
	~Enemy();

	/// override
	void Tick() override;

	/// normal

	/// get set

private:
	void ChangeDirection() override;
	void RefreshUv(const int horizontal, const int vertical) override;

	void SetRandomDirection();
	int GetMovableDirections() const;
};

