// Player.h
// represents player

#pragma once

#include "Vec2.h"
#include "Character.h"

class Player : public Character
{
public:
	static constexpr Vec2i SHEET_COUNT = { 2, 4 };
	static constexpr int ANIM_INTERVAL = 8;

private:
	Vec2i mChipIndex;

public:
	/// special
	Player();
	~Player();

	/// override
	void Tick() override;

	/// normal
	void RefreshUv(const int horizontal, const int vertical);

private:

};

