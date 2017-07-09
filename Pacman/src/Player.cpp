#include "Player.h"
#include "FieldChip.h"

Player::Player()
{
	mPos = { 5, 10 };
	InitSpriteInfo(Vec2f{ 0, 0 }, FieldChip::SIZE);
	RefreshUv(0, 0);
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
}

void Player::SetNextDirection(Direction dir)
{
	mDirection = dir;
	ChangeDirection();
}

void Player::ChangeDirection()
{
	switch (mDirection)
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
