// Billboard.h
// ビルボード1枚を管理するクラス

#pragma once

#include "Sprite.h"

class Billboard : public Sprite<4>
{
public:
	Billboard(const Vec2f& aPos, const Vec2f& aSize)
		: Sprite(aPos, aSize)
	{
		ResetUv();
	}

	~Billboard()
	{
	}

private:

};

