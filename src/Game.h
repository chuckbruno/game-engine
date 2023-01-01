#pragma once

//#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

struct Vector2
{
	float x;
	float y;
};

class Game
{

public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	SDL_Window* mWindow;
	bool mIsRunning;
	SDL_Renderer* mRenderer;
	Vector2 mCharacterPos;
	Uint32 mTicksCount;
	Vector2 mMovementDir;

};