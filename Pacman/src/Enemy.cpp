#include "Enemy.h"
#include "Random.h"
#include <algorithm>
#include <random>

extern Random random;

namespace
{
	// Yは上が若い
	constexpr Vec2i OFFSET_LIST[] = { { 0, -1 },{ 0, +1 },{ -1, 0 },{ 1, 0 } };
}

Enemy::Enemy(Field& field)
	: Character(field)
{
	//Initialize(0);
}

Enemy::~Enemy()
{
}

void Enemy::Tick()
{
	++mCounter;

	RefreshUv(mCounter / ANIM_INTERVAL % SHEET_COUNT.x, mType);

	// 移動
	if (mField.IsMovable(mPos + OFFSET_LIST[static_cast<int>(mDirection)]))
	{
		pos += mMoveSpeed;
		if (IsPassedOverDestination())
		{
			UpdatePosition();
			// ぶつかってないのなら、前と後ろとそれ以外にある場合
			if (GetMovableDirections() >= 3)
			{
				SetRandomDirection();
			}
			ChangeDirection();
		}
	}
	else
	{
		SetRandomDirection();
		ChangeDirection();
	}
}

void Enemy::Initialize(const int type)
{
	mType = type;
	mPos = mField.GetRandomPlacablePos();
	//mPos = { 1, 1 };
	InitSpriteInfo(Vec2f{ Field::BASE_POS.x + FieldChip::SIZE.x * mPos.x, Field::BASE_POS.y - FieldChip::SIZE.y * mPos.y }, FieldChip::SIZE);
	RefreshUv(0, 0);
	mDirection = Direction::Down;
	SetNextDirection(Direction::Down);
	ChangeDirection();
}

void Enemy::ChangeDirection()
{
	int dir = static_cast<int>(mNextDirection);
	Vec2f offset = OFFSET_LIST[dir];
	if (mField.IsMovable(mPos + offset))
	{
		mDirection = mNextDirection;
		RefreshUv(mChipIndex.x, mType);
		mMoveSpeed = Vec2f{ offset.x, -offset.y } * MOVE_SPEED;
	}
}

void Enemy::RefreshUv(const int horizontal, const int vertical)
{
	assert(0 <= horizontal);
	assert(horizontal < SHEET_COUNT.x);
	assert(0 <= vertical);
	assert(vertical < SHEET_COUNT.y);

	mChipIndex = { horizontal, vertical };

	// uv
	uv[0] = { 1.0f / SHEET_COUNT.x * (horizontal + 0), 1 - 1.0f / SHEET_COUNT.y * (vertical + 0) };
	uv[1] = { 1.0f / SHEET_COUNT.x * (horizontal + 1), 1 - 1.0f / SHEET_COUNT.y * (vertical + 0) };
	uv[2] = { 1.0f / SHEET_COUNT.x * (horizontal + 1), 1 - 1.0f / SHEET_COUNT.y * (vertical + 1) };
	uv[3] = { 1.0f / SHEET_COUNT.x * (horizontal + 0), 1 - 1.0f / SHEET_COUNT.y * (vertical + 1) };
}

void Enemy::SetRandomDirection()
{
	int indices[4]{ 0, 1, 2, 3 };
	int nowDir = static_cast<int>(mDirection);
	bool onlyOne = GetMovableDirections() <= 1;

	// shuffle
	for (size_t i = 0; i < 4; i++)
	{
		std::swap(indices[i], indices[random(4)]);
	}

	for (size_t i = 0; i < 4; i++)
	{
		// 真後ろ方向でないものを選択する
		if (!onlyOne && indices[i] / 2 == nowDir / 2 && indices[i] % 2 == 1 - (nowDir % 2)) continue;

		if (mField.IsMovable(mPos + OFFSET_LIST[indices[i]]))
		{
			mNextDirection = static_cast<Character::Direction>(indices[i]);
		}
	}
}

int Enemy::GetMovableDirections() const
{
	int count = 0;
	for (size_t i = 0; i < 4; i++)
	{
		if (mField.IsMovable(mPos + OFFSET_LIST[i]))
		{
			++count;
		}
	}

	return count;
}
