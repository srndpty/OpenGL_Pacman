// Field.h
// フィールドを表すクラス

#pragma once

#include "FieldChip.h"
#include "Vec2.h"

class Field
{
public:
	static constexpr Vec2i SIZE = { 20, 10 };
	static constexpr float CHIP_SIDE_LENGTH  = 0.1f;
	static constexpr Vec2f CHIP_SIZE = { CHIP_SIDE_LENGTH, CHIP_SIDE_LENGTH };
	static constexpr Vec2f BASE_POS = { -0.5f, -0.3f };
	
private:
	FieldChip mFieldChips[SIZE.y][SIZE.x];

public:
	/// special
	Field();
	~Field();

	/// normal
	void Draw(const int id);

private:

};

