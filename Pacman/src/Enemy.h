// Enemy.h
// “G‚ð•\Œ»‚·‚éƒNƒ‰ƒX

#pragma once

#include "Character.h"

class Enemy : public Character
{
public:
	Enemy(Field& field);
	~Enemy();

	/// normal

	/// get set

private:
	void ChangeDirection() override;
	void RefreshUv(const int horizontal, const int vertical) override;


};

