#include "Core/Timer.h"

Timer::Timer()
{
	reset();
}

float Timer::getDeltaTime() const
{
	return mDeltaTime.count();
}

float Timer::getGameTime() const
{
	std::chrono::duration<float, std::milli> gameTime;

	if (mStopped)
	{
		gameTime = (mStopTime - mBaseTime);
	}
	else
	{
		gameTime = ((mCurrTime - mBaseTime) - mPausedTime);
	}

	return gameTime.count();
}

void Timer::start()
{
	if (mStopped)
	{
		mCurrTime = std::chrono::high_resolution_clock::now();
		mPausedTime += (mCurrTime - mStopTime);
		mPrevTime = mCurrTime;
		mStopped = false;
	}
}

void Timer::stop()
{
	if (!mStopped)
	{
		mStopTime = std::chrono::high_resolution_clock::now();
		mStopped = true;
	}
}

void Timer::reset()
{
	auto currTime = std::chrono::high_resolution_clock::now();

	mBaseTime = currTime;
	mPrevTime = currTime;
	mCurrTime = currTime;
	mStopped = true;
}

void Timer::update()
{
	if (!mStopped)
	{
		mCurrTime = std::chrono::high_resolution_clock::now();
		mDeltaTime = mCurrTime - mPrevTime;
		mPrevTime = mCurrTime;
	}
}