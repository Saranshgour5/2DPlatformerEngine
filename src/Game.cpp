#include "Game.hpp"
#include "TextureManager.hpp"
#include <SDL2/SDL_render.h>

SDL_Renderer* Game::renderer { nullptr };

Game::Game() 
	{ }

Game::~Game()
	{ }

SDL_Texture* ground {};

void Game::init(const char* title, int width, int height, bool fullScreen)
{
	int flags {};
	if (fullScreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
		}

		isRunning = true;
	}

	ground = TextureManager::LoadTexture("assets/ground.jpg");
}


void Game::handleEvents() 
{
	SDL_Event event {};
	SDL_PollEvent(&event);

	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
	}
}

void Game::update() 
{ }

void Game::render()
{
	SDL_RenderClear(renderer);
	SDL_Rect src {0, 0, 32, 32};
	SDL_Rect dest {100, 100, 32, 32};
	TextureManager::Draw(ground, src, dest);
	SDL_RenderPresent(renderer);
}

void Game::clean() 
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
