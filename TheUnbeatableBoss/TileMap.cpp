#include"pch.h"
#include "TileMap.h"
#include"World.h"
#include"Actor.h"
Tile TileMap::TileGrid[NO_OF_ROWS][NO_OF_COLS];

void TileMap::Initialize()
{
	//Assign the grids each 
	sf::Vector2f position;
	position.x = 0;
	position.y = 0;
	for (int i = 0; i < NO_OF_ROWS; i++)
	{
		for (int j = 0; j < NO_OF_COLS; j++)
		{
			//Create a new tile and assign it's position
			TileGrid[i][j].SetIndex(i, j);
		}
	}
}

std::pair<int,int> TileMap::GetIndexForPosition(const sf::Vector2f& position)
{
	Tile* result = nullptr;
	for (int i = 0; i < NO_OF_ROWS; i++)
	{
		for (int j = 0; j < NO_OF_COLS; j++)
		{
			if (TileGrid[i][j].IsTileInPosition(position))
			{
				result = &TileGrid[i][j];
				break;
			}
		}
	}
	if (result == nullptr)
		throw std::exception("Invalid position");
	return std::pair<int, int>(result->mRowIndex, result->mColIndex);

}

void TileMap::GetPositionFromIndex(const int row,const int col, sf::Vector2f& output)
{
	output = TileGrid[row][col].mPosition;
}

bool TileMap::IsTileFree(int r, int c)
{
	auto allActorsInTheWorld = World::GetAllActorsInTheWorld();
	for (auto actor : allActorsInTheWorld)
	{
		if (actor->IsActorAlive())
		{
			auto indexOfActor = GetIndexForPosition(actor->mPosition);
			if (indexOfActor.first == r && indexOfActor.second == c)
			{
				return false;
			}
		}
	}
	return true;
}

bool TileMap::IsTileFree(const sf::Vector2f & position)
{
	auto Index = GetIndexForPosition(position);
	return IsTileFree(Index.first, Index.second);
}
