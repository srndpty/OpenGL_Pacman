// Field.h
// フィールドを表すクラス

#pragma once

#include "FieldChip.h"
#include "Vec2.h"

class Field
{
public:
	static constexpr Vec2i SIZE = { 20, 10 };
	static constexpr Vec2f BASE_POS = { -0.5f, +0.2f };
	
private:
	FieldChip mFieldChips[SIZE.y][SIZE.x];

public:
	/// special
	Field();
	~Field();

	/// normal
	void InitFromFile(const char* filename);
	void Draw(const int id);
	bool IsMovable(const int x, const int y) const;
	bool IsMovable(const Vec2i& v) const;
	void SetType(const int x, const int y, FieldChip::Type type);
	void SetType(const Vec2i& v, FieldChip::Type type);


private:

};

