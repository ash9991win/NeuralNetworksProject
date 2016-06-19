#pragma once
enum class Status { RUNNING, FINISHED };
enum class SuccessStatus { SUCCESS, FAILED };

template<class Owner>
class State {
private:
	Owner* mOwner;
protected:
	Status mRunningStatus;
	SuccessStatus mSuccessStatus;
	string mStateName;
public:
	virtual void Enter() = 0;
	virtual void Execute() = 0;
	virtual void Exit() = 0;
	void SetOwner(Owner* owner) { mOwner = owner; }
	void SetName(const string& name) { mStateName = name; }
	const string& Name() const { return mStateName; }
	Status PollStatus() const { return mRunningStatus; }
	SuccessStatus PollSuccesStatus() const { return mSuccessStatus; }
};
template<class Owner>
class StateManager
{
private:
	Owner* mOwner;
	State<Owner> *mCurrentState;
	State<Owner> *mPreviousState;
	State<Owner> *mGlobalState;
	map<std::string,State<Owner>*> mStateTable;
	map<State<Owner>*, State<Owner>*> mSuccessTransitionTable;
	map<State<Owner>*, State<Owner>*> mFailureTransitionTable;
public:
	StateManager(Owner* owner)
		:mOwner(owner), mCurrentState(nullptr), mPreviousState(nullptr), mGlobalState(nullptr)
	{
	}
	void Execute() {
		if (mCurrentState)
		{
			mCurrentState->Execute();
			if (DidStateFinish())
			{
				if (DidStateSucceed())
				{
					if (mSuccessTransitionTable.find(mCurrentState) != mSuccessTransitionTable.end())
					{
						ChangeState(mSuccessTransitionTable[mCurrentState]);
					}
				}
				else
				{
					if (mFailureTransitionTable.find(mCurrentState) != mFailureTransitionTable.end())
					{
						ChangeState(mFailureTransitionTable[mCurrentState]);

					}
				}
			}
		}
		if (mGlobalState)
		{
			mGlobalState->Execute();
		}
	}
	void ChangeState(State<Owner>* newState)
	{
		if (mCurrentState != newState && newState)
		{
			mCurrentState->Exit();
			mPreviousState = mCurrentState;
			mCurrentState = newState;
			mCurrentState->Enter();
		}
		else
		{
			RestartState();
		}
	}
	void ChangeState(const string& name)
	{
		if (mStateTable.Find(name) != mStateTable.end())
		{
			ChangeState(mStateTable[name]);
		}
	}
	void AddState(State<Owner>& newState)
	{
		mStateTable[newState.Name()] = &newState;
	}
	void AddTransition(State<Owner>& source, State<Owner>* successState, State<Owner>* failedState = nullptr)
	{
		mSuccessTransitionTable[&source] = successState;
		if (failedState)
		{
			mFailureTransitionTable[&source] = failedState;
		}
	}
	bool DidStateFinish() const
	{
		return (mCurrentState && (mCurrentState->PollStatus() == Status::FINISHED));
	}
	bool DidStateSucceed() const
	{
		return (mCurrentState && (mCurrentState->PollSuccesStatus() == SuccessStatus::SUCCESS));
	}
	void RestartState()
	{
		mCurrentState->Exit();
		mCurrentState->Enter();
	}

	void SetCurrentState(State<Owner>* state) { mCurrentState = state; }
	void SetGlobalState(State<Owner>* state) { mGlobalState = state; }
};
