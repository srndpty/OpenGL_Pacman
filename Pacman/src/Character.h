// Character.h
// represents character

#pragma once

#include "Sprite.h"
#include "Field.h"

class Character : public Sprite<4>
{
public:
	enum class Direction
	{
		Up,
		Down,
		Left,
		Right
	};

protected:
	int mCounter = 0;
	Vec2i mChipIndex;
	Vec2i mPos;
	Direction mDirection;
	Direction mNextDirection;
	Vec2f mMoveSpeed;
	Field& mField;


public:
	/// special
	Character() = delete;
	Character(Field& field);
	virtual ~Character();

	/// normal
	virtual void Tick() = 0;
	virtual void Initialize() = 0;
	
	void SetNextDirection(Direction dir);

protected:
	bool IsPassedOverDestination() const;
	void UpdatePosition();

private:
	virtual void ChangeDirection() = 0;
	virtual void RefreshUv(const int horizontal, const int vertical) = 0;

};

