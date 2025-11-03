#ifndef COLLIDERCOMPONENT_HPP
#define COLLIDERCOMPONENT_HPP

#include "Components.hpp"
#include "ECS.hpp"
#include "TransformComponent.hpp"

class ColliderComponent: public ECS::Component {
public:
	SDL_Rect colliderBox {};
	
	ColliderComponent() = default;
	ColliderComponent(float srcX, float srcY, int h, int w)
	: x(srcX), y(srcY), width(w), height(h)	
	{ 
			
	}
	void init() override
	{
		if(!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>(x, y, height, width, 1);
		}
		transform = &entity->getComponent<TransformComponent>();
		colliderBox.x = static_cast<int>(x);
		colliderBox.y = static_cast<int>(y);
		colliderBox.w = width * transform->scale;
		colliderBox.h = height * transform->scale;

	}

	void update(float mfT) override
	{
		colliderBox.x = static_cast<int>(transform->position.x * mfT);
		colliderBox.y = static_cast<int>(transform->position.y * mfT);
		colliderBox.w = transform->width * transform->scale;
		colliderBox.h = transform->height * transform->scale;
	}

private:
	TransformComponent* transform;
	float x {}, y {};
	int width{32}, height{32};
};

#endif
