// Game.h
// ゲーム全体を管理するクラス

#pragma once

#include <memory>

#include "Field.h"
#include "Player.h"
#include "Enemy.h"

class Game
{
public:
	static constexpr int ENEMY_COUNT = 4;

private:
	std::unique_ptr<Field> mField;
	std::unique_ptr<Player> mPlayer;
	std::unique_ptr<Enemy> mEnemy;

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

