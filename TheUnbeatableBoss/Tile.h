#pragma once
class Tile
{
private:
	int mRowIndex;
	int mColIndex;

	sf::Vector2f mPosition;
	void SetIndex(int r, int c);
	friend class TileMap;
	bool IsTileInPosition(const sf::Vector2f& position) const;
	bool IsEmpty;
public:
	Tile() = default;
	~Tile() = default;
};

