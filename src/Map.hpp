#ifndef MAP_HPP
#define MAP_HPP

#include <string>

class Map 
{
public:
	Map(int mMapScale, int mTileSize);
	~Map();
	
	void LoadMap(std::string path, int sizeX, int sizeY);
	void AddTile(int srcX, int srcY, int xPos, int yPos);
private:
	int mapScale {};
	int tileSize {};
	int scaledSize {};
};

#endif
