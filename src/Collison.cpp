#include "Collison.hpp"
#include "ECS/ColliderComponent.hpp"
#include <SDL2/SDL_rect.h>

bool Collison::AABB(const SDL_Rect& recA, const SDL_Rect& recB)
{
	if (
		recA.x + recA.w >= recB.x &&
		recB.x + recB.w >= recA.x &&
		recA.y + recA.h >= recB.y &&
		recB.y + recB.h >= recA.y)
	{
		return true;
	}

	return false;
}

bool Collison::AABB(const ColliderComponent& A, const ColliderComponent&B)
{
	return AABB(A.colliderBox, B.colliderBox);
}
