
#include "Game.h"
#include "Input.h"
#include "Collision.h"

Game::Game()
	: mField(std::make_unique<Field>())
	, mPlayer(std::make_unique<Player>(*mField))
	, mEnemy(std::make_unique<Enemy>(*mField))
{
}

Game::~Game()
{
}

void Game::Initialize()
{
	mField->Initialize();
	mPlayer->Initialize();
	mEnemy->Initialize();
}

void Game::SetTexId(const int numId, const int pacmanId, const int fieldId, const int enemyId)
{
	mTextureId[TEXID_DIGIT] = numId;
	mTextureId[TEXID_PACMAN] = pacmanId;
	mTextureId[TEXID_FIELD] = fieldId;
	mTextureId[TEXID_ENEMY] = enemyId;
}

// ret: clear true
bool Game::Tick()
{
	if (mField->GetFoodCount() == 0)
	{
		std::cout << "game clear! press R to restart.\n";
		return true;
	}

	// 同じ座標だったらゲームオーバー
	if (Collision::IsHitSqSq(mEnemy.get(), mPlayer.get()))
	{
		std::cout << "game over! press R to restart.\n";
		return true;
	}

	// 入力制御
	if (input.GetButtomDown(GLFW_KEY_W))
	{
		mPlayer->SetNextDirection(Player::Direction::Up);
	}
	else if (input.GetButtomDown(GLFW_KEY_S))
	{
		mPlayer->SetNextDirection(Player::Direction::Down);
	}
	else if (input.GetButtomDown(GLFW_KEY_A))
	{
		mPlayer->SetNextDirection(Player::Direction::Left);
	}
	else if (input.GetButtomDown(GLFW_KEY_D))
	{
		mPlayer->SetNextDirection(Player::Direction::Right);
	}

	// プレイヤー移動
	mEnemy->Tick();
	mPlayer->Tick();

	return false;
}

void Game::Draw()
{
	mField->Draw(mTextureId[TEXID_FIELD]);
	mEnemy->Draw(mTextureId[TEXID_ENEMY]);
	mPlayer->Draw(mTextureId[TEXID_PACMAN]);
}
