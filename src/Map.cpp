#include "Map.hpp"
#include <cstdlib>
#include <fstream>
#include <iterator>
#include "ECS/ECS.hpp"
#include "ECS/TileComponent.hpp"

extern ECS::Manager manager;

Map::Map(int mMapScale, int mTileSize): mapScale(mMapScale), tileSize(mTileSize) 
{
	scaledSize = mMapScale * mTileSize;
}

Map::~Map() 
	{ }

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
	char c {};
	std::fstream mapFile {};
	mapFile.open(path);

	int srcX {}, srcY {};
	std::cout << sizeX << ' ' << sizeY << std::endl;
	for(int y {}; y < sizeY; ++y) {
		for(int x {}; x < sizeX; ++x)
		{
			mapFile.get(c);
			srcY = (c - '0') * tileSize;
			std::cout << c;
			mapFile.get(c);
			srcX = (c - '0') * tileSize;
			std::cout << c <<',';
			AddTile(srcX, srcY, x * scaledSize, y * scaledSize);
			mapFile.ignore();
		}
		std::cout << std::endl;
	}

	mapFile.close();
}

void Map::AddTile(int srcX, int srcY, int xPos, int yPos)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xPos, yPos, tileSize, mapScale);
} 
