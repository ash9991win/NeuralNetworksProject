#include"pch.h"
#include "Tile.h"

void Tile::SetIndex(int r, int c)
{
	mRowIndex = r;
	mColIndex = c;
	mPosition.x = r * TILE_WIDTH;
	mPosition.y = c * TILE_HEIGHT;
}

bool Tile::IsTileInPosition(const sf::Vector2f & position) const
{
	return ((position.x >= mPosition.x) && (position.x <= (mPosition.x + TILE_WIDTH)) && (position.y >= mPosition.y) && (position.y <= (mPosition.y + TILE_HEIGHT)));
}
