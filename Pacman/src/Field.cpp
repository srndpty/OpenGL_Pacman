
#include "Field.h"

Field::Field()
{
	// チップの初期化
	for (size_t i = 0; i < SIZE.y; i++)
	{
		for (size_t j = 0; j < SIZE.x; j++)
		{
			mFieldChips[i][j].Initialize(Vec2f{ BASE_POS.x + CHIP_SIZE.x * j / 2, BASE_POS.y + CHIP_SIZE.y / 2 * i }, CHIP_SIZE);
		}
	}
}

Field::~Field()
{
}

void Field::Draw(const int id)
{
	// チップの描画
	for (size_t i = 0; i < SIZE.y; i++)
	{
		for (size_t j = 0; j < SIZE.x; j++)
		{
			mFieldChips[i][j].Draw(id);
		}
	}

}
