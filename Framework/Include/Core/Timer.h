#pragma once

#include "Core/StdHeaders.h"
#include <chrono>

class Timer
{
public:

  Timer();

  float getDeltaTime() const;
  float getGameTime() const;

  void start();
  void stop();
  void reset();
  void update();

private:

  std::chrono::duration<float, std::milli> mDeltaTime{ 0 };
  std::chrono::duration<float, std::milli> mPausedTime{ 0 };
  std::chrono::high_resolution_clock::time_point mBaseTime;
  std::chrono::high_resolution_clock::time_point mStopTime;
  std::chrono::high_resolution_clock::time_point mPrevTime;
  std::chrono::high_resolution_clock::time_point mCurrTime;
  bool mStopped{ false }; 
};