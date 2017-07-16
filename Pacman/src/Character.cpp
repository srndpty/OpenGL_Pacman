#include "Character.h"


Character::Character(Field & field)
	: mField(field)
{
}

Character::~Character()
{
}

void Character::SetNextDirection(Direction dir)
{
	mNextDirection = dir;
}

void Character::UpdatePosition()
{
	switch (mDirection)
	{
	case Character::Direction::Up:
		--mPos.y;
		break;
	case Character::Direction::Down:
		++mPos.y;
		break;
	case Character::Direction::Left:
		--mPos.x;
		break;
	case Character::Direction::Right:
		++mPos.x;
		break;
	default:
		SHOULD_NOT_REACH_HERE();
		break;
	}

	//std::cout << "position updated (" << mPos.x << ", " << mPos.y << ")\n";

	// Œµ–§‚ÉˆÊ’u’²®
	pos.x = Field::BASE_POS.x + FieldChip::SIZE.x * mPos.x;
	pos.y = Field::BASE_POS.y - FieldChip::SIZE.y * mPos.y;
}

bool Character::IsPassedOverDestination() const
{
	Vec2i offset;

	switch (mDirection)
	{
	case Character::Direction::Up:
		return pos.y >= Field::BASE_POS.y - (mPos.y - 1) * FieldChip::SIZE.y;
	case Character::Direction::Down:
		return pos.y <= Field::BASE_POS.y - (mPos.y + 1) * FieldChip::SIZE.y;
	case Character::Direction::Left:
		return pos.x <= Field::BASE_POS.x + (mPos.x - 1) * FieldChip::SIZE.x;
	case Character::Direction::Right:
		return pos.x >= Field::BASE_POS.x + (mPos.x + 1) * FieldChip::SIZE.x;
	default:
		SHOULD_NOT_REACH_HERE();
		break;
	}

	return false;
}

