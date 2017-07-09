// Game.h
// ゲーム全体を管理するクラス

#pragma once

#include "Field.h"
#include "Player.h"

class Game
{
private:
	Field mField;
	Player mPlayer;

public:
	/// special
	Game();
	~Game();

	/// normal
	void SetTexId(const int numId, const int pacmanId, const int fieldId);
	void Tick();
	void Draw();

private:
	int mNumId;
	int mPacmanId;
	int mFieldId;
};

