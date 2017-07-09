
#include <fstream>
#include <string>
#include <sstream>

#include "Field.h"

Field::Field()
{
	// チップの初期化
	for (size_t i = 0; i < SIZE.y; i++)
	{
		for (size_t j = 0; j < SIZE.x; j++)
		{
			// yはマイナス方向へ
			mFieldChips[i][j].Initialize(Vec2f{ BASE_POS.x + CHIP_SIZE.x * j / 2, BASE_POS.y - CHIP_SIZE.y / 2 * i }, CHIP_SIZE);
		}
	}

	InitFromFile("res/field1.txt");
}

Field::~Field()
{
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
