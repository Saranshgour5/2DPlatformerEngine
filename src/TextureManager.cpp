#include "TextureManager.hpp"

SDL_Texture* TextureManager::LoadTexture(const char *fileName)
{
	SDL_Surface* tempSurface = IMG_Load(fileName);
	if(!tempSurface) {
		std::cout << fileName << "\n";
		std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
	}
	SDL_Texture* texture { SDL_CreateTextureFromSurface(Game::renderer, tempSurface) };
	SDL_FreeSurface(tempSurface);
	if(!texture) {
		if(!Game::renderer) { std::cout << "Null Renderer\n"; }
		std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
	}
	return texture;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest) 
{
	if (tex) {
		SDL_RenderCopy(Game::renderer, tex, &src, &dest);
	} else {
		std::cerr << "Texture is null, cannot draw." << std::endl;
	}
}
