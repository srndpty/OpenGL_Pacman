
#include "Game.h"
#include "Input.h"

Game::Game()
	: mField(std::make_unique<Field>())
	, mPlayer(std::make_unique<Player>(*mField))
{
}

Game::~Game()
{
}

void Game::SetTexId(const int numId, const int pacmanId, const int fieldId)
{
	mNumId = numId;
	mPacmanId = pacmanId;
	mFieldId = fieldId;
}

void Game::Tick()
{
	if (mField->GetFoodCount() == 0)
	{
		std::cout << "game clear!\n";
		return;
	}

	// ���͐���
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

	// �v���C���[�ړ�
	mPlayer->Tick();
}

void Game::Draw()
{
	mField->Draw(mFieldId);
	mPlayer->Draw(mPacmanId);
}
