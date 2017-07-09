#include "Player.h"
#include "FieldChip.h"
#include "Field.h"

namespace 
{
	// Yは上が若い
	Vec2i OFFSET_LIST[] = { {0, -1}, {0, +1}, {-1, 0}, {1, 0} };
}

Player::Player(Field & field)
	: mField(field)
{
	mPos = { 1, 4 };
	InitSpriteInfo(Vec2f{ Field::BASE_POS.x + FieldChip::SIZE.x * mPos.x, Field::BASE_POS.y - FieldChip::SIZE.y * mPos.y }, FieldChip::SIZE);
	RefreshUv(0, 0);
	mDirection = Direction::Up;
	SetNextDirection(Direction::Up);
	ChangeDirection();
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

}

void Player::UpdatePosition()
{
	switch (mDirection)
	{
	case Player::Direction::Up:
		--mPos.y;
		break;
	case Player::Direction::Down:
		++mPos.y;
		break;
	case Player::Direction::Left:
		--mPos.x;
		break;
	case Player::Direction::Right:
		++mPos.x;
		break;
	default:
		SHOULD_NOT_REACH_HERE();
		break;
	}

	std::cout << "position updated (" << mPos.x << ", " << mPos.y << ")\n";

	// アイテム取得
	mField.SetType(mPos, FieldChip::Type::Empty);

	// 厳密に位置調整
	pos.x = Field::BASE_POS.x + FieldChip::SIZE.x * mPos.x;
	pos.y = Field::BASE_POS.y - FieldChip::SIZE.y * mPos.y;
}

bool Player::IsPassedOverDestination() const
{
	Vec2i offset;

	switch (mDirection)
	{
	case Player::Direction::Up:
		return pos.y >= Field::BASE_POS.y - (mPos.y - 1) * FieldChip::SIZE.y;
	case Player::Direction::Down:
		return pos.y <= Field::BASE_POS.y - (mPos.y + 1) * FieldChip::SIZE.y;
	case Player::Direction::Left:
		return pos.x <= Field::BASE_POS.x + (mPos.x - 1) * FieldChip::SIZE.x;
	case Player::Direction::Right:
		return pos.x >= Field::BASE_POS.x + (mPos.x + 1) * FieldChip::SIZE.x;
	default:
		SHOULD_NOT_REACH_HERE();
		break;
	}

	return false;
}

void Player::SetNextDirection(Direction dir)
{
	mNextDirection = dir;
}

void Player::ChangeDirection()
{
	Vec2i offset;

	switch (mNextDirection)
	{
	case Player::Direction::Up:
		offset = { 0, +1 };
		if (mField.IsMovable(mPos + -offset))
		{
			mDirection = mNextDirection;
			RefreshUv(mChipIndex.x, 0);
			mMoveSpeed = offset.AsFloat() * MOVE_SPEED;
		}
		else
		{
			offset = { 0, 0 };
		}
		break;
	case Player::Direction::Down:
		offset = { 0, -1 };
		if (mField.IsMovable(mPos + -offset))
		{
			mDirection = mNextDirection;
			RefreshUv(mChipIndex.x, 1);
			mMoveSpeed = offset.AsFloat() * MOVE_SPEED;
		}
		else
		{
			offset = { 0, 0 };
		}
		break;
	case Player::Direction::Left:
		offset = { -1, 0 };
		if (mField.IsMovable(mPos + offset))
		{
			mDirection = mNextDirection;
			RefreshUv(mChipIndex.x, 2);
			mMoveSpeed = offset.AsFloat() * MOVE_SPEED;
		}
		else
		{
			offset = { 0, 0 };
		}
		break;
	case Player::Direction::Right:
		offset = { +1, 0 };
		if (mField.IsMovable(mPos + offset))
		{
			mDirection = mNextDirection;
			RefreshUv(mChipIndex.x, 3);
			mMoveSpeed = offset.AsFloat() * MOVE_SPEED;
		}
		else
		{
			offset = { 0, 0 };
		}
		break;
	default:
		SHOULD_NOT_REACH_HERE();
		break;
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

void Player::SetFieldRef(const Field & field)
{
	mField = field;
}
