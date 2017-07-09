// Player.h
// represents player

#pragma once

#include "Vec2.h"
#include "Character.h"

class Player : public Character
{
public:
	enum class Direction
	{
		Up,
		Down,
		Left,
		Right
	};

	static constexpr Vec2i SHEET_COUNT = { 2, 4 };
	static constexpr int ANIM_INTERVAL = 8;
	static constexpr float MOVE_SPEED = 0.002f;

private:
	Vec2i mChipIndex;
	Direction mDirection;
	Vec2f mMoveSpeed;

public:
	/// special
	Player();
	~Player();

	/// override
	void Tick() override;

	/// normal
	void SetNextDirection(Direction dir);
	void ChangeDirection();
	void RefreshUv(const int horizontal, const int vertical);

private:

};

