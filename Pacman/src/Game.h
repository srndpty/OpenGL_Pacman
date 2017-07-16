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
	std::unique_ptr<Enemy> mEnemy;
	int mTextureId[TEXID_MAX];

	int mNumId;
	int mPacmanId;
	int mFieldId;

public:
	/// special
	Game();
	~Game();

	/// normal
	void Initialize();
	void SetTexId(const int numId, const int pacmanId, const int fieldId, const int enemyId);
	void Tick();
	void Draw();

};

