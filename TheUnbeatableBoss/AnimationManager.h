#pragma once
//The animation manager will be spawned in the world 
//every actor can have one and they will say play this animation
//and the animation manager will change that actor's sprite accordingly
#include"Component.h"
//The different animations present
enum class AnimationID
{
	PlayerIdleAnimation, BossIdleAnimation, PlayerRightWalkAnimation,PlayerLeftWalkAnimation
};
//An animation structure
struct Animation
{
	int startFrame;
	int endFrame;
	int currentFrame;
	float timeBetween;
	int currentIndex;
	Actor* owner;
	std::vector<sf::Sprite> Frames;
};
class AnimationManager : public Component
{
private:
	//A map of an animation id with it's assosciated animation
	std::map<AnimationID, Animation> mAnimationTable;
	Animation* mCurrentAnimation;
	void AddAnimation(AnimationID id, int startFrame, int lastFrame, Actor* owner, float timeBetween = 0.13f);
	void AddAnimation(AnimationID id);
public:
	//Play a given animation 
	void PlayAnimation(AnimationID id);
	// Inherited via Actor
	virtual void Update(float deltaTime) override;
	virtual void BeginPlay() override;
};