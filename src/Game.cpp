#include "Game.hpp"
#include "ECS/ECS.hpp"
#include "TextureManager.hpp"
#include "ECS/Components.hpp"
#include "Map.hpp"

SDL_Renderer* Game::renderer { nullptr };
SDL_Event Game::event {};

Game::Game() 
	{ }

Game::~Game()
	{ }

Map* map {};
SDL_Texture* ground {};
ECS::Manager manager {};
auto& player{ manager.addEntity() };

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
	
	map = new Map(1, 32);
	map->LoadMap("assets/tileMap.map", 30, 20);
	player.addComponent<TransformComponent>();
	player.addComponent<KeyboardController>();
	player.addComponent<SpriteComponent>();

	ground = TextureManager::LoadTexture("assets/ground.jpg");
}


void Game::handleEvents() 
{
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
{
	manager.refresh();
	manager.update(1.0f);
}

void Game::render()
{
	SDL_RenderClear(renderer);
	SDL_Rect src {0, 0, 32, 32};
	SDL_Rect dest {100, 100, 32, 32};
	TextureManager::Draw(ground, src, dest);
	manager.draw();
	SDL_RenderPresent(renderer);
}

void Game::clean() 
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
