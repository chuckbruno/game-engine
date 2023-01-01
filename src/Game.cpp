#include "Game.h"

#include <iostream>

Game::Game()
{
	mWindow = nullptr;
	mIsRunning = true;
}

bool Game::Initialize()
{
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0)
	{
		SDL_Log("Failed to initialize the library");
		return false;
	}

	mWindow = SDL_CreateWindow("Game Engine", 100, 100, 1024, 768, 0);
	if (!mWindow)
	{
		SDL_Log("Failed to create the window");
		return false;
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	mCharacterPos.x = (1024.0f - 100.0f) / 2.0f;
	mCharacterPos.y = (768.0f - 100.0f) / 2.0f;

	return true;
}

void Game::Shutdown()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;

		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	mMovementDir.x = 0;
	mMovementDir.y = 0;

	if (state[SDL_SCANCODE_W])
	{
		mMovementDir.y -= 1;
	}
	if (state[SDL_SCANCODE_S])
		mMovementDir.y += 1;

	if (state[SDL_SCANCODE_A])
		mMovementDir.x -= 1;
	if (state[SDL_SCANCODE_D])
		mMovementDir.x += 1;
}

void Game::UpdateGame()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	mTicksCount = SDL_GetTicks();

	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	mCharacterPos.x += mMovementDir.x * 300.0f * deltaTime;
	mCharacterPos.y += mMovementDir.y * 300.0f * deltaTime;

	float minXPos = 100.0f / 2.0f;
	float minYPos = 100.0f / 2.0f;

	float maxXPos = 1024.0f - 100.0f / 2.0f;
	float maxYPos = 768.0f - 100.0f / 2.0f;

	if (mCharacterPos.x < minXPos)
	{
		mCharacterPos.x = minXPos;
	}
	else if (mCharacterPos.x > maxXPos)
	{
		mCharacterPos.x = maxXPos;
	}

	if (mCharacterPos.y < minYPos)
	{
		mCharacterPos.y = minYPos;
	}
	else if (mCharacterPos.y > maxYPos)
	{
		mCharacterPos.y = maxYPos;
	}
}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mRenderer);

	SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
	
	SDL_Rect character{
		static_cast<int>(mCharacterPos.x - 50),
		static_cast<int>(mCharacterPos.y - 50),
		100, 100
	};

	SDL_RenderFillRect(mRenderer, &character);
	SDL_RenderPresent(mRenderer);
}