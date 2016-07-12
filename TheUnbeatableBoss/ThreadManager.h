#pragma once
#include<future>
class ThreadManager
{
private:
	static vector<future<void>> threads;
	static map<std::string, std::function<void()>> mFunctionTable;
public:
	void static CreateThread(std::string id,function<void()> fun);
	void static StartThread(std::string id);
	void static FinishThreads();
	ThreadManager();
	~ThreadManager();
};
