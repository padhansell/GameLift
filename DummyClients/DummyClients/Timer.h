#pragma once

#include <chrono>
#include "Job.h"


class AsyncExecutable;

struct TimerJobElement
{
	TimerJobElement(AsyncExecutable* owner, JobEntry* task, int64_t execTick)
		: mOwner(owner), mTask(task), mExecutionTick(execTick)
	{}

	AsyncExecutable*	mOwner;
	JobEntry*			mTask;
	int64_t				mExecutionTick;
};

struct TimerJobComparator
{
	bool operator()(const TimerJobElement& lhs, const TimerJobElement& rhs)
	{
		return lhs.mExecutionTick > rhs.mExecutionTick;
	}
};


typedef std::priority_queue<TimerJobElement, std::vector<TimerJobElement>, TimerJobComparator> TimerJobPriorityQueue;

class Timer
{
public:

	Timer();

	void PushTimerJob(AsyncExecutable* obj, uint32_t after, JobEntry* task);

	void DoTimerJob();

private:

	TimerJobPriorityQueue	mTimerJobQueue;

};


