#pragma once

#include "Core/Singleton.h"

enum class LogLevel
{
  Info,
  Debug,
  Warning,
  Error,
  Fatal
};

class Logger : public Singleton<Logger>
{
public:

  Logger() = default;
  virtual ~Logger() = default;

  LogLevel getMaxLogLevel() const
  {
    return mMaxLogLevel;
  }

  bool canLog(LogLevel logLevel) const;
  void setMaxLogLevel(LogLevel logLevel);

  template <typename ... Args>
  void info(const char* format, Args&&... args) 
  {
    if (canLog(LogLevel::Info))
    {
      write(LogLevel::Info, format, std::forward<Args>(args)...);
    }
  }

  template <typename ... Args>
  void debug(const char* format, Args&&... args) 
  {
    if (canLog(LogLevel::Debug))
    {
      write(LogLevel::Debug, format, std::forward<Args>(args)...);
    }
  }

  template <typename ... Args>
  void warning(const char* format, Args&&... args) 
  {
    if (canLog(LogLevel::Warning))
    {
      write(LogLevel::Warning, format, std::forward<Args>(args)...);
    }
  }

  template <typename ... Args>
  void error(const char* format, Args&&... args) 
  {
    if (canLog(LogLevel::Error))
    {
      write(LogLevel::Error, format, std::forward<Args>(args)...);
    }
  }

  template <typename ... Args>
  void fatal(const char* format, Args&&... args) 
  {
    if (canLog(LogLevel::Fatal))
    {
      write(LogLevel::Fatal, format, std::forward<Args>(args)...);
    }
  }

  virtual void write(LogLevel logLevel, const char* format, ...);

protected:

  LogLevel mMaxLogLevel{ LogLevel::Error };
};