// Billboard.h
// �r���{�[�h1�����Ǘ�����N���X

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

