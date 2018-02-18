
#include <fstream>
#include <string>
#include <sstream>

#include "Field.h"
#include "Random.h"

extern Random random;

Field::Field()
{
	Initialize(1);
}

Field::~Field()
{
}

void Field::Initialize(const int stage)
{
	// チップの初期化
	for (size_t i = 0; i < SIZE.y; i++)
	{
		for (size_t j = 0; j < SIZE.x; j++)
		{
			// yはマイナス方向へ
			mFieldChips[i][j].Initialize(Vec2f{ BASE_POS.x + FieldChip::SIZE.x * j, BASE_POS.y - FieldChip::SIZE.y * i }, FieldChip::SIZE);
		}
	}

	std::stringstream ss;
	ss << "res/field" << stage << ".txt";

	InitFromFile(ss.str().c_str());
}

void Field::InitFromFile(const char * filename)
{
	std::ifstream file(filename);

	if (!file)
	{
		std::cerr << "file not found:" << filename << "\n";
		return;
	}

	// 1行ずつ処理
	std::string str;
	int width, height;
	bool isSizeResolved = false;
	int line = 0;
	while (std::getline(file, str))
	{
		// スラッシュ2個で始まる行は無視
		if (str.length() >= 2 && str[0] == '/' && str[1] == '/') continue;

		// sizeが決定していないならその確定が先
		if (!isSizeResolved)
		{
			std::stringstream ss(str);

			if (!(ss >> width >> height))
			{
				// width, heightの読み込みに失敗
				std::cerr << "Failed to load width, height of the field file: " << filename << "\n";
				return;
			}

			// 成功したら次へ
			isSizeResolved = true;
			continue;
		}

		// 幅高さのチェック
		if (line > height)
		{
			std::cerr << "Over reading line index:" << line << " max:" << height << "\n";
			continue;
		}

		if (str.length() < width)
		{
			std::cout << "Insufficient width:" << str.length() << " expected:" << width << "\n";
			continue;
		}

		// 各行の処理
		for (size_t i = 0; i < width; i++)
		{
			int id = str[i] - '0';
			mFieldChips[line][i].RefreshUv(id);
		}

		// 次の行へ
		++line;
	}
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

bool Field::IsMovable(const int x, const int y) const
{
	auto type = mFieldChips[y][x].GetType();
	return type == FieldChip::Type::Empty || type == FieldChip::Type::Food;
}

bool Field::IsMovable(const Vec2i& v) const
{
	return IsMovable(v.x, v.y);
}

void Field::SetType(const int x, const int y, FieldChip::Type type)
{
	mFieldChips[y][x].SetType(type);
}

void Field::SetType(const Vec2i & v, FieldChip::Type type)
{
	SetType(v.x, v.y, type);
}

int Field::GetFoodCount() const
{
	int count = 0;
	for (size_t i = 0; i < SIZE.y; i++)
	{
		for (size_t j = 0; j < SIZE.x; j++)
		{
			if (mFieldChips[i][j].GetType() == FieldChip::Type::Food)
			{
				++count;
			}
		}
	}

	return count;
}

Vec2i Field::GetRandomPlacablePos()
{
	int x, y;
	do
	{
		x = random(SIZE.x);
		y = random(SIZE.y);
	} while (!IsMovable(x, y));

	return Vec2i(x, y);
}
