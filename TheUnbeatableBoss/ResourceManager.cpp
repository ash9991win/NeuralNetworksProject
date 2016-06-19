#include "pch.h"
#include "ResourceManager.h"
std::map<std::string, sf::Sprite> ResourceManager::mSpriteTable;
std::map<std::string, sf::Texture> ResourceManager::mTextureTable;
std::map<std::string, sf::Sprite>::iterator ResourceManager::mSpriteIterator;
sf::Font ResourceManager::mFont;
ResourceManager::ResourceManager()
{
}

void ResourceManager::InitializeResources()
{
	mTextureTable["boss"].loadFromFile("Resources/boss/boss-spritesheet-04.png");
	mTextureTable["player"].loadFromFile("Resources/rancho-spritesheet.png");
	mTextureTable["background0"].loadFromFile("Resources/Background-00.png");
	mTextureTable["background1"].loadFromFile("Resources/Background-01.png");
	mTextureTable["background2"].loadFromFile("Resources/Background-02.png");
	mTextureTable["background3"].loadFromFile("Resources/Background-03.png");
	mTextureTable["background4"].loadFromFile("Resources/Background-04.png");
	mTextureTable["background5"].loadFromFile("Resources/Background-05.png");
	mTextureTable["background6"].loadFromFile("Resources/Background-06.png");
	mTextureTable["background7"].loadFromFile("Resources/Background-07.png");
	mTextureTable["background8"].loadFromFile("Resources/Background-08.png");
	mSpriteTable["boss"] = sf::Sprite(mTextureTable["boss"]);
	mSpriteTable["player"] = sf::Sprite(mTextureTable["player"]);
	mSpriteTable["background0"] = sf::Sprite(mTextureTable["background0"]);
	mSpriteTable["background1"] = sf::Sprite(mTextureTable["background1"]);
	mSpriteTable["background2"] = sf::Sprite(mTextureTable["background2"]);
	mSpriteTable["background3"] = sf::Sprite(mTextureTable["background3"]);
	mSpriteTable["background4"] = sf::Sprite(mTextureTable["background4"]);
	mSpriteTable["background5"] = sf::Sprite(mTextureTable["background5"]);
	mSpriteTable["background6"] = sf::Sprite(mTextureTable["background6"]);
	mSpriteTable["background7"] = sf::Sprite(mTextureTable["background7"]);
	mSpriteTable["background8"] = sf::Sprite(mTextureTable["background8"]);
	mSpriteTable["Player0"] = sf::Sprite(mTextureTable["player"], sf::IntRect(0, 0, (380 / 8), (225 / 5)));
	mSpriteTable["Boss0"] = sf::Sprite(mTextureTable["boss"], sf::IntRect(0, 0, 30, 30));
	mFont.loadFromFile("C:/Windows/Fonts/arial.ttf");
}
sf::Sprite * ResourceManager::LoadSprite(std::string name)
{
	mSpriteIterator = mSpriteTable.find(name);
	if (mSpriteIterator == mSpriteTable.end())
	{
		return nullptr;
	}
	return &mSpriteIterator->second;
}

sf::Font * ResourceManager::GetGameFont()
{
	return &mFont;
}


ResourceManager::~ResourceManager()
{
}
