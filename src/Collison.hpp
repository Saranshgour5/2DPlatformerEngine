#ifndef COLLISON_HPP
#define COLLISON_HPP

#include "ECS/ColliderComponent.hpp"
#include <SDL2/SDL_rect.h>

struct Collison {
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
	static bool AABB(const ColliderComponent& A, const ColliderComponent&B);
};
#endif
