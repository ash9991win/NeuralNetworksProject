#pragma once
#include"Actor.h"
//The action class ( a player or a boss can perform a certain action)
// Typically, the boss will perform an action from it's list of actions
// When an action is predicted by the Boss for the player, then on successful prediction 
// the most effective action for that particual player's action is performed by the boss

//O
enum class ActionState
{
	STARTED,RUNNING,EXITING
};

class Action : public enable_shared_from_this<Action>
{
private:
	ActionState mCurrentState;
	double mEffectiveness;
protected:
	Actor* mOwner;
	string mName;
public:
	inline float Effectiveness() const { return mEffectiveness; }
	inline void IncreaseEffectiveness(float effFactor = 0.25) { mEffectiveness += effFactor; }
	inline void DecreaseEffectiveness(float effFactor = 0.25) { mEffectiveness -= effFactor; }
	inline ActionState GetState() const { return mCurrentState; }
	inline void ChangeState(ActionState state) { mCurrentState = state; }
	inline void SetOwner(Actor* owner) { mOwner = owner; }
	Action(string name);
	const string& Name() const { return mName; }
	~Action();
	// Inherited via Component
	virtual void Update(float deltaTime) = 0 ;
	virtual void BeginPlay() = 0  ;
	RTTI_DECLARATION(Action, Action);
};

