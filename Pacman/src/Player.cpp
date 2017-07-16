#include "Player.h"
#include "FieldChip.h"
#include "Field.h"

namespace 
{
	// Yは上が若い
	constexpr Vec2i OFFSET_LIST[] = { {0, -1}, {0, +1}, {-1, 0}, {1, 0} };
}

Player::Player(Field & field)
	: Character(field)
{
	Initialize();
}

Player::~Player()
{
}

void Player::Tick()
{
	++mCounter;

	RefreshUv(mCounter / ANIM_INTERVAL % SHEET_COUNT.x, mChipIndex.y);

	// 移動
	if (mField.IsMovable(mPos + OFFSET_LIST[static_cast<int>(mDirection)]))
	{
		pos += mMoveSpeed;
		if (IsPassedOverDestination())
		{
			UpdatePosition();
			ChangeDirection();
		}
	}
	else
	{
		ChangeDirection();
	}

	// プレイヤーはアイテムを取得する
	GetItem();
}

void Player::Initialize()
{
	mPos = { 1, 4 };
	InitSpriteInfo(Vec2f{ Field::BASE_POS.x + FieldChip::SIZE.x * mPos.x, Field::BASE_POS.y - FieldChip::SIZE.y * mPos.y }, FieldChip::SIZE);
	RefreshUv(0, 0);
	mDirection = Direction::Up;
	SetNextDirection(Direction::Up);
	ChangeDirection();
}


void Player::ChangeDirection()
{
	int dir = static_cast<int>(mNextDirection);
	Vec2f offset = OFFSET_LIST[dir];
	if (mField.IsMovable(mPos + offset))
	{
		mDirection = mNextDirection;
		RefreshUv(mChipIndex.x, dir);
		mMoveSpeed = Vec2f{ offset.x, -offset.y } * MOVE_SPEED;
	}
}

void Player::RefreshUv(const int horizontal, const int vertical)
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

void Player::GetItem()
{
	// アイテム取得
	mField.SetType(mPos, FieldChip::Type::Empty);
}

