#ifndef SPRITECOMPONENT_HPP
#define SPRITECOMPONENT_HPP

#include "ECS.hpp"
#include "TransformComponent.hpp"
#include "../TextureManager.hpp"
#include <SDL2/SDL_rect.h>

class SpriteComponent: public ECS::Component 
{
private:
	TransformComponent* transform {};
	SDL_Texture* texture {};
	SDL_Rect src {}, dest {};

public:
	SpriteComponent() = default;

	void init() override 
	{
		transform = &entity->getComponent<TransformComponent>();
		src.x = 0, src.y = 0;
		src.w = transform->width, src.h = transform->height;
		texture = TextureManager::LoadTexture("assets/ground.jpg");
	}

	void update(float mFT) override
	{
		dest.x = transform->position.x * mFT;
		dest.y = transform->position.y * mFT;
		dest.w = transform->width * transform->scale;
		dest.h = transform->height * transform->scale;
	}

	void draw() override 
	{
		TextureManager::Draw(texture, src, dest);
	}
};

#endif
