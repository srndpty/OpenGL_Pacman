#include "FieldChip.h"



FieldChip::FieldChip()
{
}

FieldChip::FieldChip(const Vec2f& aPos, const Vec2f& aSize)
	: Sprite(aPos, aSize)
{
}


FieldChip::~FieldChip()
{
}

void FieldChip::Initialize(const Vec2f & aPos, const Vec2f & aSize)
{
	Sprite::Initialize(aPos, aSize);
	RefreshUv(0);
}

void FieldChip::RefreshUv(const int index)
{
	assert(0 <= index);
	assert(index < CHIP_MAX);
	uv[0] = { 1.0f / CHIP_MAX * index,       0.0f };
	uv[1] = { 1.0f / CHIP_MAX * index,       1.0f };
	uv[2] = { 1.0f / CHIP_MAX * (index + 1), 1.0f };
	uv[3] = { 1.0f / CHIP_MAX * (index + 1), 0.0f };
}
