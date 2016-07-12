#pragma once
#include "Component.h"

//The action class ( a player or a boss can perform a certain action)
// Typically, the boss will perform an action from it's list of actions
// When an action is predicted by the Boss for the player, then on successful prediction 
// the most effective action for that particual player's action is performed by the boss

//O
enum class ActionState
{
	STARTED,RUNNING,EXITING
};
class Action :
	public Component
{
private:
	ActionState mCurrentState;
	float mEffectiveness;
public:
	inline float Effectiveness() const { return mEffectiveness; }
	inline void IncreaseEffectiveness(float effFactor = 0.25) { mEffectiveness += effFactor; }
	inline void DecreaseEffectiveness(float effFactor = 0.25) { mEffectiveness -= effFactor; }
	inline ActionState GetState() const { return mCurrentState; }
	inline void ChangeState(ActionState state) { mCurrentState = state; }
	Action();
	~Action();

	// Inherited via Component
	virtual void Update(float deltaTime) override;
	virtual void BeginPlay() override;
};

