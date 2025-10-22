#pragma once

#include "../Game.hpp"
#include "ECS.hpp"
#include "TransformComponent.hpp"

class KeyboardController : public ECS::Component
{
public:
	TransformComponent *transform;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
	}

	void update(float mFT) override
	{
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = -1 * mFT;
				std::cout << "Pressing w" << std::endl;
				break;
			case SDLK_a:
				transform->velocity.x = -1 * mFT;
				std::cout << "Pressing a" << std::endl;
				break;
			case SDLK_d:
				transform->velocity.x = 1 * mFT;
				break;
			case SDLK_s:
				transform->velocity.y = 1 * mFT;
				break;
			default:
				break;
			}
		}
	
		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = 0;
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				break;
			case SDLK_ESCAPE:
				Game::isRunning = false;
			default:
				break;
			}
		}
	}
};
