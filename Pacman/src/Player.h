// Player.h
// represents player

#pragma once

#include "Vec2.h"
#include "Character.h"
#include "Field.h"

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
	Vec2i mPos;
	Direction mDirection;
	Direction mNextDirection;
	Vec2f mMoveSpeed;
	Field& mField;

public:
	/// special
	Player() = delete;
	Player(Field& field);
	~Player();

	/// override
	void Tick() override;

	/// normal
	void UpdatePosition();
	bool IsPassedOverDestination() const;
	void SetNextDirection(Direction dir);
	void ChangeDirection();
	void RefreshUv(const int horizontal, const int vertical);

	/// get set
	void SetFieldRef(const Field& field);

private:

};

