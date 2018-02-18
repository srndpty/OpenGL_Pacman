#include "Collision.h"

#include "Character.h"

const float HitFix = 0.5f;

bool Collision::IsHitSqSq(const Character * a, const Character * b)
{
	if (a->pos.x + a->size.x / 2 * HitFix >= b->pos.x - b->size.x / 2 * HitFix)
	{
		if (a->pos.x - a->size.x / 2 * HitFix <= b->pos.x + b->size.x / 2 * HitFix)
		{
			if (a->pos.y + a->size.y / 2 * HitFix >= b->pos.y - b->size.y / 2 * HitFix)
			{
				if (a->pos.y - a->size.y / 2 * HitFix <= b->pos.y + b->size.y / 2 * HitFix)
				{
					return true;
				}
			}
		}
	}

	return false;
}
