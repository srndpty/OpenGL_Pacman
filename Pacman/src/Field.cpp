
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
	// �`�b�v�̏�����
	for (size_t i = 0; i < SIZE.y; i++)
	{
		for (size_t j = 0; j < SIZE.x; j++)
		{
			// y�̓}�C�i�X������
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

	// 1�s������
	std::string str;
	int width, height;
	bool isSizeResolved = false;
	int line = 0;
	while (std::getline(file, str))
	{
		// �X���b�V��2�Ŏn�܂�s�͖���
		if (str.length() >= 2 && str[0] == '/' && str[1] == '/') continue;

		// size�����肵�Ă��Ȃ��Ȃ炻�̊m�肪��
		if (!isSizeResolved)
		{
			std::stringstream ss(str);

			if (!(ss >> width >> height))
			{
				// width, height�̓ǂݍ��݂Ɏ��s
				std::cerr << "Failed to load width, height of the field file: " << filename << "\n";
				return;
			}

			// ���������玟��
			isSizeResolved = true;
			continue;
		}

		// �������̃`�F�b�N
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

		// �e�s�̏���
		for (size_t i = 0; i < width; i++)
		{
			int id = str[i] - '0';
			mFieldChips[line][i].RefreshUv(id);
		}

		// ���̍s��
		++line;
	}
}

void Field::Draw(const int id)
{
	// �`�b�v�̕`��
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
