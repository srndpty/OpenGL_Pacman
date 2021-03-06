#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <memory>
#include "linmath.h"

// lib headers
#include "Shader.h"
#include "Vec2.h"
#include "Def.h"
#include "Input.h"
#include "Sprite.h"
#include "BmpLoader.h"
#include "Random.h"
#include "NumDisp.h"
#include "Billboard.h"

// game specific headers
#include "Game.h"



#pragma comment(lib, "opengl32.lib")

Input input;
Shader shader;
Random random;

namespace
{
	enum class GameState
	{
		Init,
		Main,
		Gameover,
		GameClear,
	};

	const char* GAME_TITLE = "Pacman";
	const int STAGE_MAX = 3;

	// window
	GLFWwindow* window = nullptr;

	// main game
	GameState gameState = GameState::Init;
	std::unique_ptr<Game> game = std::make_unique<Game>();

	auto scoreDispBlack = std::make_unique<NumDisp<2>>(Vec2f{ +0.5f, 0.4f });
	auto scoreDispWhite = std::make_unique<NumDisp<2>>(Vec2f{ +0.5f, 0.2f });
	bool firstGameOver = true;
	int scorePoint = 0;
	int stage = 0;

	// test
	std::unique_ptr<Billboard> test0 = std::make_unique<Billboard>(Vec2f{ 0, -0.3f }, Vec2f{ 0.2f, 0.2f });
	std::unique_ptr<Billboard> test1 = std::make_unique<Billboard>(Vec2f{ 0, +0.3f }, Vec2f{ 0.2f, 0.2f });

	// texture ids
	GLuint pacmanId;
	GLuint fieldId;
	GLuint enemyId;
	GLuint numId;
}


//----------------------------------------
// エラーコールバック
void ErrorCallback(int error, const char* description)
{
	std::cerr << "Error Occured code: " << error << " desc: " << description << "\n";
}

//----------------------------------------
// 入力コールバック
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		input.mKeyStates[key].pressed = true;
	}
	else if (action == GLFW_RELEASE)
	{
		input.mKeyStates[key].pressed = false;
	}

	// ESCで終了
	if (input.mKeyStates[GLFW_KEY_ESCAPE].pressed)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

//----------------------------------------
// カーソル移動コールバック
void CursorPosCallBack(GLFWwindow* window, double xpos, double ypos)
{
	static double pastx = 0, pasty = 0;
	if (pastx == xpos && pasty == ypos)
	{
		return;
	}

	// カーソル位置更新
	input.mCursorPos = { static_cast<int>(xpos), static_cast<int>(ypos) };
	//std::cout << "cursor pos x: " << xpos << " y: " << ypos << "\n";
}

//----------------------------------------
// マウスクリックコールバック
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		input.mMouseStates[button].pressed = true;
		//std::cout << "mouse " << button << " pressed!\n";
	}

	//if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	//{

	//}
}

//----------------------------------------
// 描画
void Draw()
{
	// 画面の初期化
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearDepth(1.0);

	//scoreDispBlack->Draw(numId);
	//scoreDispWhite->Draw(numId);

	game->Draw();

}

//----------------------------------------
// ライブラリの初期化
int LibInit()
{
	std::cout << "current directory is " << GetCurrentWorkingDir().c_str() << "\n";

	if (!glfwInit())
	{
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	window = glfwCreateWindow(WINDOW_SIZE.x, WINDOW_SIZE.y, GAME_TITLE, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwSetErrorCallback(ErrorCallback);
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, CursorPosCallBack);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);

	// モニタとの同期
	glfwMakeContextCurrent(window);
	auto addr = (GLADloadproc)glfwGetProcAddress;
	gladLoadGLLoader(addr);
	glfwSwapInterval(1);

	return 0;
}

//----------------------------------------
// 初期化
void Init()
{
	game->Initialize(stage);
	gameState = GameState::Main;
	std::cout << "Game Start!\n";
}

//----------------------------------------
// メインの処理
void GameMain()
{
	// ゲーム更新
	if (game->Tick())
	{
		if (game->IsCleared())
		{
			stage++;
			if (stage >= STAGE_MAX)
			{
				gameState = GameState::GameClear;
			}
			else
			{
				gameState = GameState::Init;
			}
		}
		else
		{
			gameState = GameState::Gameover;
		}
	}

	// ゲーム中もRで最初から
	if (input.mKeyStates[GLFW_KEY_R].pressed)
	{
		gameState = GameState::Init;
	}
}

//----------------------------------------
// ゲームオーバー
void GameOver()
{
	if (input.mKeyStates[GLFW_KEY_R].pressed)
	{
		stage = 0;
		gameState = GameState::Init;
	}
}

//----------------------------------------
// ゲームクリア
void GameClear()
{
	if (input.mKeyStates[GLFW_KEY_R].pressed)
	{
		stage = 0;
		gameState = GameState::Init;
	}
}

//----------------------------------------
// ENTRY POINT
int main()
{
	if (LibInit())
	{
		return -1;
	}

	// shader
	shader.SetUp();

	// load images
	numId = LoadBmp("images/num.bmp");
	pacmanId = LoadBmp("images/pacman.bmp");
	fieldId = LoadBmp("images/field.bmp");
	enemyId = LoadBmp("images/enemy.bmp");
	game->SetTexId(numId, pacmanId, fieldId, enemyId);

	float ratio;
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;


	// ゲームループ
	while (!glfwWindowShouldClose(window))
	{
		// -- 計算 --
		switch (gameState)
		{
		case GameState::Init:
			Init();
			break;
		case GameState::Main:
			GameMain();
			break;
		case GameState::Gameover:
			GameOver();
			break;
		case GameState::GameClear:
			GameClear();
			break;
		default:
			std::cout << "unknown state\n";
			break;
		}

		input.Update();
		input.ResetNow();

		// -- 描画 -- 
		Draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}