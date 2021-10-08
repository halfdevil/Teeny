#pragma once

#include "Core/StdHeaders.h"

template <typename ...Args>
class Observer
{
public:

  void subscribe(std::function<void(Args&&...)> subscriber)
  {
    mSubscribers.push_back(std::move(subscriber));
  }

  void notify(Args... args)
  {
    for (auto& subscriber : mSubscribers)
    {
      subscriber(args...);
    }
  }

private:

  std::vector<std::function<void(Args...)>> mSubscribers;
};