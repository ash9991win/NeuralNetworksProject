#pragma once
#include"pch.h"
#include "Component.h"
class AnimationComponent :
	public Component
{
private:
	std::vector<sf::Sprite> mFrames;
	float mTimeBetweenFrames;
	float mCurrentTime;
	int mCurrentFrame;
	int mMaxFrame;
	float mFrameWidth;
	float mFrameHeight;
public:
	AnimationComponent();
	void SetFrames(std::vector<std::string> frameNames);
	void SetTimeBetweenFrames(float value);
	void SetFrameDimensions(float width = 100, float height = 100);
	~AnimationComponent();

	// Inherited via Component
	virtual void Update(float deltaTime) override;
	virtual void BeginPlay() override;
};

