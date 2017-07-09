// FieldChip.h
// フィールドの1マス

#pragma once

#include "Sprite.h"

class FieldChip : public Sprite<4>
{
public:
	static constexpr int CHIP_MAX = 4;

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

