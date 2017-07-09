#include "Player.h"
#include "FieldChip.h"

Player::Player()
{
	Initialize(Vec2f{ 0, 0 }, FieldChip::SIZE);
	RefreshUv(0, 0);
}

Player::~Player()
{
}

void Player::Tick()
{
	++mCounter;

	RefreshUv(mCounter / ANIM_INTERVAL % SHEET_COUNT.x, mChipIndex.y);
}

void Player::RefreshUv(const int horizontal, const int vertical)
{
	assert(0 <= horizontal);
	assert(horizontal < SHEET_COUNT.x);

	mChipIndex = { horizontal, vertical };

	// uv
	uv[0] = { 1.0f / SHEET_COUNT.x * (horizontal + 0), 1 - 1.0f / SHEET_COUNT.y * (vertical + 0) };
	uv[1] = { 1.0f / SHEET_COUNT.x * (horizontal + 1), 1 - 1.0f / SHEET_COUNT.y * (vertical + 0) };
	uv[2] = { 1.0f / SHEET_COUNT.x * (horizontal + 1), 1 - 1.0f / SHEET_COUNT.y * (vertical + 1) };
	uv[3] = { 1.0f / SHEET_COUNT.x * (horizontal + 0), 1 - 1.0f / SHEET_COUNT.y * (vertical + 1) };
}
