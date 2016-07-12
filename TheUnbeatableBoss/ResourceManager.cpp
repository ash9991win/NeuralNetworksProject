#include "pch.h"
#include "ResourceManager.h"
std::map<std::string, sf::Sprite> ResourceManager::mSpriteTable;
std::map<std::string, sf::Texture> ResourceManager::mTextureTable;
std::map<int, sf::Sprite> ResourceManager::mAnimationTable;
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


	mSpriteTable["background0"] = sf::Sprite(mTextureTable["background0"]);
	mSpriteTable["background1"] = sf::Sprite(mTextureTable["background1"]);
	mSpriteTable["background2"] = sf::Sprite(mTextureTable["background2"]);
	mSpriteTable["background3"] = sf::Sprite(mTextureTable["background3"]);
	mSpriteTable["background4"] = sf::Sprite(mTextureTable["background4"]);
	mSpriteTable["background5"] = sf::Sprite(mTextureTable["background5"]);
	mSpriteTable["background6"] = sf::Sprite(mTextureTable["background6"]);
	mSpriteTable["background7"] = sf::Sprite(mTextureTable["background7"]);
	mSpriteTable["background8"] = sf::Sprite(mTextureTable["background8"]);

	mSpriteTable["boss"] = sf::Sprite(mTextureTable["boss"]);
	mSpriteTable["player"] = sf::Sprite(mTextureTable["player"]);

	mSpriteTable["PlayerIdle_1"] = sf::Sprite(mTextureTable["player"], sf::IntRect(9,162,24,30));
	mSpriteTable["PlayerIdle_2"] = sf::Sprite(mTextureTable["player"], sf::IntRect(46, 162, 24, 30));
	mSpriteTable["PlayerIdle_3"] = sf::Sprite(mTextureTable["player"], sf::IntRect(85, 162, 24, 30));
	mSpriteTable["PlayerIdle_4"] = sf::Sprite(mTextureTable["player"], sf::IntRect(122, 162, 24, 30));
	mSpriteTable["PlayerIdle_5"] = sf::Sprite(mTextureTable["player"], sf::IntRect(161, 162, 24, 30));

	mSpriteTable["PlayerWalk_1"] = sf::Sprite(mTextureTable["player"], sf::IntRect(9,9,24,30));
	mSpriteTable["PlayerWalk_2"] = sf::Sprite(mTextureTable["player"], sf::IntRect(46, 9, 24, 30));
	mSpriteTable["PlayerWalk_3"] = sf::Sprite(mTextureTable["player"], sf::IntRect(85, 9, 24, 30));
	mSpriteTable["PlayerWalk_4"] = sf::Sprite(mTextureTable["player"], sf::IntRect(122, 9, 24, 30));
	mSpriteTable["PlayerWalk_5"] = sf::Sprite(mTextureTable["player"], sf::IntRect(161, 9, 24, 30));

	mSpriteTable["BossIdle_1"] = sf::Sprite(mTextureTable["boss"], sf::IntRect(30, 0, -30, 30));
	mSpriteTable["BossIdle_2"] = sf::Sprite(mTextureTable["boss"], sf::IntRect(60, 0, -30, 30));
	mSpriteTable["BossIdle_3"] = sf::Sprite(mTextureTable["boss"], sf::IntRect(90, 0, -30, 30));
	mSpriteTable["BossIdle_4"] = sf::Sprite(mTextureTable["boss"], sf::IntRect(120, 0, -30, 30));
	mSpriteTable["BossIdle_5"] = sf::Sprite(mTextureTable["boss"], sf::IntRect(150, 0, -30, 30));

	//mSpriteTable["Boss0"] = sf::Sprite(mTextureTable["boss"], sf::IntRect(0, 0, -30, 30));
	mAnimationTable[0] = sf::Sprite(mTextureTable["boss"], sf::IntRect(30, 0, -30, 30));
	mAnimationTable[1] = sf::Sprite(mTextureTable["boss"], sf::IntRect(60, 0, -30, 30));
	mAnimationTable[2] = sf::Sprite(mTextureTable["boss"], sf::IntRect(90, 0, -30, 30));
	mAnimationTable[3] = sf::Sprite(mTextureTable["boss"], sf::IntRect(120, 0,-30, 30));
	mAnimationTable[4] = sf::Sprite(mTextureTable["boss"], sf::IntRect(150, 0, -30, 30));

	
	mAnimationTable[5] = sf::Sprite(mTextureTable["player"], sf::IntRect(9, 162, 24, 30));
	mAnimationTable[6] = sf::Sprite(mTextureTable["player"], sf::IntRect(46, 162, 24, 30));
	mAnimationTable[7] = sf::Sprite(mTextureTable["player"], sf::IntRect(85, 162, 24, 30));
	mAnimationTable[8] = sf::Sprite(mTextureTable["player"], sf::IntRect(122, 162, 24, 30));
	mAnimationTable[9] = sf::Sprite(mTextureTable["player"], sf::IntRect(161, 162, 24, 30));
	mAnimationTable[10] = sf::Sprite(mTextureTable["player"], sf::IntRect(9, 9, 24, 30));
	mAnimationTable[11] = sf::Sprite(mTextureTable["player"], sf::IntRect(46, 9, 24, 30));
	mAnimationTable[12] = sf::Sprite(mTextureTable["player"], sf::IntRect(85, 9, 24, 30));
	mAnimationTable[13] = sf::Sprite(mTextureTable["player"], sf::IntRect(122, 9, 24, 30));
	mAnimationTable[14] = sf::Sprite(mTextureTable["player"], sf::IntRect(161, 9, 24, 30));

	mAnimationTable[15] = sf::Sprite(mTextureTable["player"], sf::IntRect(9, 9, 24, 30));
	mAnimationTable[16] = sf::Sprite(mTextureTable["player"], sf::IntRect(46, 9, 24, 30));
	mAnimationTable[17] = sf::Sprite(mTextureTable["player"], sf::IntRect(85, 9, 24, 30));
	mAnimationTable[18] = sf::Sprite(mTextureTable["player"], sf::IntRect(122, 9, 24, 30));
	mAnimationTable[19] = sf::Sprite(mTextureTable["player"], sf::IntRect(161, 9, 24, 30));
	mAnimationTable[15].setScale(-1, 1);
	mAnimationTable[16].setScale(-1, 1);
	mAnimationTable[17].setScale(-1, 1);
	mAnimationTable[18].setScale(-1, 1);
	mAnimationTable[19].setScale(-1, 1);

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

sf::Sprite * ResourceManager::LoadAnimationFrame(int id)
{
	return &mAnimationTable[id];
}

sf::Font * ResourceManager::GetGameFont()
{
	return &mFont;
}


ResourceManager::~ResourceManager()
{
}
