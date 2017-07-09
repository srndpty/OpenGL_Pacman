
#include "Game.h"

Game::Game()
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
	mPlayer.Tick();
}

void Game::Draw()
{
	mField.Draw(mFieldId);
	mPlayer.Draw(mPacmanId);
}
