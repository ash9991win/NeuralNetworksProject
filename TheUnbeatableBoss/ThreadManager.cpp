#include"pch.h"
#include "ThreadManager.h"
#include<functional>
map<std::string, std::function<void()>> ThreadManager::mFunctionTable;
vector<future<void>> ThreadManager::threads;
void ThreadManager::CreateThread(std::string id, function<void()> fun)
{
	mFunctionTable[id] = fun;
}
void ThreadManager::StartThread(std::string id)
{
	if (mFunctionTable.find(id) != mFunctionTable.end())
	{
		auto fn = mFunctionTable[id];
		threads.emplace_back(std::async([fn]() {fn(); }));
	}
}
void ThreadManager::FinishThreads()
{
	for (auto& thread : threads)
	{
		thread.get();
	}
}
ThreadManager::ThreadManager()
{
}
ThreadManager::~ThreadManager()
{
	FinishThreads();
}
