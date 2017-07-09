#include "Player.h"
#include "FieldChip.h"
#include "Field.h"

Player::Player()
{
	mPos = { 5, 5 };
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

	// ˆÚ“®
	pos += mMoveSpeed;

	if (IsPassedOverDestination())
	{
		UpdatePosition();
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
	//ChangeDirection();
}

void Player::ChangeDirection()
{
	switch (mNextDirection)
	{
	case Player::Direction::Up:
		mMoveSpeed = { 0, +MOVE_SPEED };
		RefreshUv(mChipIndex.x, 0);
		break;
	case Player::Direction::Down:
		mMoveSpeed = { 0, -MOVE_SPEED };
		RefreshUv(mChipIndex.x, 1);
		break;
	case Player::Direction::Left:
		mMoveSpeed = { -MOVE_SPEED, 0 };
		RefreshUv(mChipIndex.x, 2);
		break;
	case Player::Direction::Right:
		mMoveSpeed = { +MOVE_SPEED, 0 };
		RefreshUv(mChipIndex.x, 3);
		break;
	default:
		SHOULD_NOT_REACH_HERE();
		break;
	}

	mDirection = mNextDirection;
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
