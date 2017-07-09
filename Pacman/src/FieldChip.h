// FieldChip.h
// �t�B�[���h��1�}�X

#pragma once

#include "Sprite.h"

class FieldChip : public Sprite<4>
{
public:
	static constexpr int CHIP_MAX = 4;

public:
	/// special
	FieldChip();
	FieldChip(const Vec2f& aPos, const Vec2f& aSize);
	~FieldChip();

	/// normal
	void Initialize(const Vec2f& aPos, const Vec2f& aSize);
	void RefreshUv(const int index);
};

