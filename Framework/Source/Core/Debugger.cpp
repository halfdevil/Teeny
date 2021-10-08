#include "Core/Debugger.h"
#include "Core/Core.h"

void Debugger::assert(bool condition, const char* fileName, uint32_t lineNo, const char* format, ...)
{
  constexpr uint32_t MAX_BUFFER_LINE = 4096;

  if (!condition)
  {
    char buffer[MAX_BUFFER_LINE];

    va_list args;

    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);

    LOGERROR("!!ASSERT!! at (%s, %d): %s", fileName, lineNo, buffer);
    abort();
  }
}

void Debugger::fatal(bool condition, const char* fileName, uint32_t lineNo, const char* format, ...)
{
  constexpr uint32_t MAX_BUFFER_LINE = 4096;

  if (!condition)
  {
    char buffer[MAX_BUFFER_LINE];

    va_list args;

    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);

    LOGFATAL("(%s, %d): %s", fileName, lineNo, buffer);
    exit(EXIT_FAILURE);
  }
}