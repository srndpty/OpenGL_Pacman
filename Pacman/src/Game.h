// Game.h
// �Q�[���S�̂��Ǘ�����N���X

#pragma once

#include "Field.h"

class Game
{
private:
	Field mField;

public:
	/// special
	Game();
	~Game();

	/// normal
	void SetTexId(const int numId, const int pacmanId, const int fieldId);
	void Draw();

private:
	int mNumId;
	int mPacmanId;
	int mFieldId;
};

