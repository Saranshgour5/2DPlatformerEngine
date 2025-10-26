#ifndef TILECOMPONENT_HPP
#define TILECOMPONENT_HPP

#include "ECS.hpp"
#include "../TextureManager.hpp"

class TileComponent: public ECS::Component
{
public:
	SDL_Texture* texture {};
	SDL_Rect srcRect {}, destRect {};

	TileComponent() = default;

	~TileComponent() 
	{
		SDL_DestroyTexture(texture);
	}

	TileComponent(int srcX, int srcY, int xPos, int yPos, int tileSize, int tileScale)
	{
		texture = TextureManager::LoadTexture("assets/Terrain-ss.png");
		srcRect.x = srcX, srcRect.y = srcY;
		//std::cout << srcRect.x << ' ' << srcRect.y << '\n';
		srcRect.w = srcRect.h = tileSize;
		destRect.x = xPos;
		destRect.y = yPos;
		destRect.w = destRect.h = tileSize * tileScale;
	}

	void draw() override 
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}

};

#endif
