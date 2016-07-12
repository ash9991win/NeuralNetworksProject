#pragma once
#include<future>
//The timer class runs a timer on a thread and calls a delegate back to it
class Timer
{
private:
	//List of timers in the world
	static vector<Timer*> mListOfTimers;
	//Threads for each timer
	static std::vector<std::future<void>> mTimerThreads;
	//The mutex for a timer
	std::mutex mTimerMutex;
	//A flag to check if the timer is running or no
	bool mIsRunning;
	//Whether the timer has started
	bool mStarted;
	//The maximum amount of time that the timer will run to
	float mMaxRunningTime;
	//The time between frames ( I capture this every frame so that the threads don't end up deadlocking)
	float mDeltaTime;
	//The elapsed time of the timer
	float mElapsedTime;
	Timer(float maxTime) :mMaxRunningTime(maxTime), mDeltaTime(0), mElapsedTime(0), mIsRunning(false),mStarted(false)
	{

	}
	friend class World;
	//Make the main() function a friend because the main() is responsible for
	//stopping the timer threads once the world is shutdown
	friend int main();
	//Returns true if the timer has finished
	bool DidTimerFinish() const;
public:
	//The delegate for updation of timer
	delegate<void, float> UpdateDelegate;
	//The delegate to invoke once the timer has finished running
	delegate<void> FinishedDelegate;
	void Update(float deltaTime);
	//Start the timer ( this invokes the thread to run the timer)
	void StartTimer();
	Timer();
	~Timer();
};

