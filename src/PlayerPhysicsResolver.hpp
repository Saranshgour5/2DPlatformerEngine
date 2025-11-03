#pragma once
#include "ECS/ECS.hpp"
#include "ECS/PhysicsComponent2.hpp"
#include "ECS/ColliderComponent.hpp"
#include "Collison.hpp"

#include "Game.hpp"
#include <SDL2/SDL_rect.h>
#include <cmath>

struct PlayerPhysicsResolver: public PhysicsResolver
{
public: 
	PlayerPhysicsResolver() = default;
	void update(float mFT, ECS::Entity* entity, ECS::Manager& manager) override
	{

		auto& colliders {manager.getEntitiesByGroup(static_cast<std::size_t>(Game::groupLabels::Colliders)) };
		auto& transform = entity->getComponent<TransformComponent>();
		
		bool isFloating = true;
		bool isWallattached = false;
		transform.accelaration.y = 4;
		MoveX(transform.velocity.x * transform.speed * mFT, entity, manager);	
		MoveY((transform.velocity.y * transform.speed + transform.accelaration.y) * mFT, entity, manager);
		/*
		for(const auto& c: colliders) {
			auto& player = entity->getComponent<ColliderComponent>();
			auto& box = c->getComponent<ColliderComponent>();
			if(Collison::AABB(player, box))
			{
				isFloating = false;
				std::cout  << box.colliderBox.y << ' ' << player.colliderBox.y << ' ' << transform.position.y << '\n';
				if(box.colliderBox.y >= player.colliderBox.y) {
					std::cout << "Colliding below\n";
						transform.position.y += (box.colliderBox.y - player.colliderBox.y - player.colliderBox.h);
					transform.velocity.y = 0;
				}
				else {
					transform.position.y += (box.colliderBox.y + box.colliderBox.h - player.colliderBox.y);
					transform.velocity.y = 0;
					std::cout << "Colliding up\n";
				}
			}
		}
		*/
	};
private:
	void MoveX(float amount, ECS::Entity* entity, ECS::Manager& manager)
	{
		static float xRemainder {};
		xRemainder += amount;
		int move = std::round(xRemainder);
		auto& transform = entity->getComponent<TransformComponent>();
		auto& colliders {manager.getEntitiesByGroup(static_cast<std::size_t>(Game::groupLabels::Colliders)) };

		std::cout << "Move " << move << '\n';
		if(move != 0) {
			xRemainder -= move;
			int sign = (move > 0) ? 1 : -1;
			SDL_Rect playerColliderBox = entity->getComponent<ColliderComponent>().colliderBox; 
			
			bool isSafeToMOve = true;
			while(move != 0)
			{
				playerColliderBox.x += sign;
				for(const auto& c : colliders) {
					auto& box = c->getComponent<ColliderComponent>();
					if(Collison::AABB(playerColliderBox, box.colliderBox))
					{
						isSafeToMOve = false;
					}
				}
				if(isSafeToMOve) {
					transform.position.x += sign;
					move -= sign;
				}
				else 
				{
					transform.velocity.x = 0;
					break;
				}
			}
		}
	}
	
	void MoveY(float amount, ECS::Entity* entity, ECS::Manager& manager)
	{
	
		static float yRemainder {};
		yRemainder += amount;
		int move = std::round(yRemainder);
		auto& transform = entity->getComponent<TransformComponent>();
		auto& colliders {manager.getEntitiesByGroup(static_cast<std::size_t>(Game::groupLabels::Colliders)) };
		std::cout << "Move " << move << '\n';
		if(move != 0) {
			yRemainder -= move;
			int sign = (move > 0) ? 1 : -1;
			SDL_Rect playerColliderBox = entity->getComponent<ColliderComponent>().colliderBox; 
			
			bool isSafeToMOve = true;
			while(move != 0)
			{
				playerColliderBox.y += sign;
				for(const auto& c : colliders) {
					auto& box = c->getComponent<ColliderComponent>();
					if(Collison::AABB(playerColliderBox, box.colliderBox))
					{
						isSafeToMOve = false;
					}
				}
				if(isSafeToMOve) {
					transform.position.y += sign;
					move -= sign;
				}
				else 
				{
					auto& keyboardComponent = entity->getComponent<KeyboardController>();
					keyboardComponent.isGrounded = true;
					transform.velocity.y = 0;
					break;
				}
			}
		}

		transform.velocity.y = 0;
	}
};
