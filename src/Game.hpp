#pragma once

#ifndef GAME_HPP
#define GAME_HPP

//#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <particle.hpp>


class Game
{

public:
	Game();

	// Initialize the game
	bool Initialize();

	// Run the game loop
	void RunLoop();

	// Cleanup and shut down the game
	void Shutdown();

private:
	void ProcessInput();

	void UpdateGame();

	void GenerateOutput();

	SDL_Window* mWindow;

	SDL_Renderer* mRenderer;

	Uint32 mTicksCount;

	bool mIsRunning;

	Particle* mCharacter;
};

#endif
