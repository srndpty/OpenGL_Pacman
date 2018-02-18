// Game.h
// ゲーム全体を管理するクラス

#pragma once

#include <memory>
#include <vector>

#include "Field.h"
#include "Player.h"
#include "Enemy.h"

class Game
{
public:
	// texture id
	enum 
	{
		TEXID_DIGIT,
		TEXID_PACMAN,
		TEXID_FIELD,
		TEXID_ENEMY,

		TEXID_MAX,
	};

	static constexpr int ENEMY_COUNT = 4;

private:
	std::unique_ptr<Field> mField;
	std::unique_ptr<Player> mPlayer;
	std::vector<std::unique_ptr<Enemy>> mEnemy;
	int mTextureId[TEXID_MAX];

	int mNumId;
	int mPacmanId;
	int mFieldId;
	bool mIsCleared = false;

public:
	/// special
	Game();
	~Game();

	/// normal
	void Initialize(const int stage);
	void SetTexId(const int numId, const int pacmanId, const int fieldId, const int enemyId);
	bool Tick();
	void Draw();
	bool IsCleared();
};

