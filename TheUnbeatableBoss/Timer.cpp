#include"pch.h"
#include "Timer.h"
vector<Timer*> Timer::mListOfTimers;
std::vector<std::future<void>> Timer::mTimerThreads;
bool Timer::DidTimerFinish() const
{
	return !mIsRunning && mStarted;
}
void Timer::Update(float deltaTime)
{
	{
		std::lock_guard<std::mutex> lg(mTimerMutex);
			mDeltaTime = deltaTime;
	}
	UpdateDelegate.Invoke(mElapsedTime);
}

void Timer::StartTimer()
{
	mIsRunning = true;
	mStarted = true;
	mTimerThreads.emplace_back((std::async([this]() {
		sf::Clock timerClock;
		timerClock.restart();
		while (timerClock.getElapsedTime().asSeconds() < mMaxRunningTime)
		{
			mElapsedTime = timerClock.getElapsedTime().asSeconds();
		}
		{
			std::lock_guard<std::mutex> lg(mTimerMutex);
			mIsRunning = false;
		}
		FinishedDelegate.Invoke();
	})));
}

Timer::Timer()
{
}


Timer::~Timer()
{
	
}
