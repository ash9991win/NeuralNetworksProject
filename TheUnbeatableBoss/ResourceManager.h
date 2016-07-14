#pragma once
#include"pch.h"
#include<map>
#include<iterator>
#include<SFML/Graphics.hpp>
/*!
\class ResourceManager
\brief The ResourceManager loads all the necessary resources 
*/
class ResourceManager
{
private:
	
	static std::map<std::string, sf::Sprite> mSpriteTable;
	static std::map<std::string, sf::Texture> mTextureTable;
	static std::map<std::string, sf::Sprite>::iterator mSpriteIterator;
	static std::map<int, sf::Sprite> mAnimationTable;
	static sf::Font mFont;
public:
	ResourceManager();
	/*!
	\fn InitializeResources()
	\brief Loads all the resources necessary for the game
	*/
	static void InitializeResources();
	/*!
	\fn LoadSprite(std::string)
	\brief Loads a sprite of the given name
	\param The name of the sprite to be loaded
	*/
	static sf::Sprite* LoadSprite(std::string name);
	static sf::Sprite* LoadAnimationFrame(int id);
	/*!
	\fn GetGameFont()
	\brief Returns the font used in the game
	*/
	static const sf::Font* GetGameFont();
	~ResourceManager();
};

