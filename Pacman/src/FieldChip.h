// FieldChip.h
// フィールドの1マス

#pragma once

#include "Sprite.h"

class FieldChip : public Sprite<4>
{
public:
	static constexpr int CHIP_MAX = 4;
	static constexpr float SIDE_LENGTH = 0.1f;
	static constexpr Vec2f SIZE = { SIDE_LENGTH, SIDE_LENGTH };

private:
	int mChipId;

public:
	/// special
	FieldChip();
	FieldChip(const Vec2f& aPos, const Vec2f& aSize);
	~FieldChip();

	/// normal
	void Initialize(const Vec2f& aPos, const Vec2f& aSize);
	void RefreshUv(const int index);
};

