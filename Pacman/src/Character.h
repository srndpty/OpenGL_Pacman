// Character.h
// represents character

#pragma once

#include "Sprite.h"

class Character : public Sprite<4>
{
protected:
	int mCounter = 0;

public:
	/// special
	Character();
	virtual ~Character();

	/// normal
	virtual void Tick() = 0;

private:

};

