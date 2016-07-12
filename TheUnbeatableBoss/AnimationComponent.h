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
	bool autoPlay;
	AnimationComponent(bool play = true);
	void SetFrames(std::vector<std::string> frameNames);
	void SetTimeBetweenFrames(float value);
	void SetFrameDimensions(float width = 100, float height = 100);
	~AnimationComponent();

	// Inherited via Component
	virtual void Update(float deltaTime) override;
	void PlayNext();
	void PlayPrev();
	void Stop();
	virtual void BeginPlay() override;
};

