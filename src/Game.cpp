#include "Game.hpp"
#include "ECS/ECS.hpp"
#include "TextureManager.hpp"
#include "ECS/Components.hpp"
#include "Map.hpp"
#include <cstddef>

#include "PlayerPhysicsResolver.hpp"

SDL_Renderer* Game::renderer { nullptr };
SDL_Event Game::event {};

Game::Game() 
	{ }

Game::~Game()
	{ }

Map* map {};
ECS::Manager manager {};
auto& player{ manager.addEntity() };

auto& tiles(manager.getEntitiesByGroup(static_cast<int>(Game::groupLabels::Maps)));
auto& players(manager.getEntitiesByGroup(static_cast<int>(Game::groupLabels::Players)));

auto& colliders(manager.getEntitiesByGroup(static_cast<std::size_t>(Game::groupLabels::Colliders)));

PlayerPhysicsResolver* physicsResolver = new PlayerPhysicsResolver();
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
	player.addComponent<TransformComponent>(100, 100);
	player.addComponent<SpriteComponent>("assets/player.png");
	player.addComponent<ColliderComponent>();
	player.addComponent<PhysicsComponent2>(manager, physicsResolver); 
	player.addComponent<KeyboardController>();
	player.addGroup(static_cast<std::size_t>(groupLabels::Players));
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
	for(auto& t : tiles)
	{
		t->draw(); 
	}
	for(auto& p: players)
	{
		p->draw();
	}
	for(auto& c: colliders)
	{
		c->draw();
	}
	SDL_RenderPresent(renderer);
}

void Game::clean() 
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
