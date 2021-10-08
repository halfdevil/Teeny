#pragma once

#include "Core/Singleton.h"

class Debugger : public Singleton<Debugger>
{
public:

  void assert(bool condition, const char* fileName, uint32_t lineNo, const char* format, ...);
  void fatal(bool condition, const char* fileName, uint32_t lineNo, const char* format, ...);
};