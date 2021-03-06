#pragma once

#include "Core/StdHeaders.h"

template <typename T>
class Singleton
{
public:

	Singleton()
	{
		mInstance = static_cast<T*>(this);
	}

	static T* getPtr()
	{
		return mInstance;
	}

	static T& get()
	{
		return *mInstance;
	}

private:

	inline static T* mInstance{ nullptr };
};