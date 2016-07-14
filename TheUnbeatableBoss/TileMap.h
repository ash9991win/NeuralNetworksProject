#pragma once
#include"Tile.h"
class TileMap
{
private:
	static Tile TileGrid[NO_OF_ROWS][NO_OF_COLS];
public:
	static void Initialize();
	static std::pair<int,int> GetIndexForPosition(const sf::Vector2f& position);
	static void GetPositionFromIndex(const int row,const int col, sf::Vector2f& ouput);
	static bool IsTileFree(int r, int c);
	static bool IsTileFree(const sf::Vector2f& position);
	TileMap() = default;
	~TileMap() = default;
};

