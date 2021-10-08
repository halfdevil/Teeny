#pragma once

#include "Core/Logger.h"
#include "Core/Debugger.h"

#define LOGINFO(format, ...) Logger::get().info("(%s:%d)"##format, __FILE__, __LINE__, ##__VA_ARGS__)
#define LOGDEBUG(format, ...) Logger::get().debug("(%s:%d)"##format, __FILE__, __LINE__, ##__VA_ARGS__)
#define LOGWARNING(format, ...) Logger::get().warning("(%s:%d)"##format, __FILE__, __LINE__, ##__VA_ARGS__)
#define LOGERROR(format, ...) Logger::get().error("(%s:%d)"##format, __FILE__, __LINE__, ##__VA_ARGS__)
#define LOGFATAL(format, ...) Logger::get().fatal("(%s:%d)"##format, __FILE__, __LINE__, ##__VA_ARGS__)

#ifdef DEBUG_BUILD
#define ASSERT(condition, format, ...) Debugger::get().assert((condition), __FILE__, __LINE__, format, ##__VA_ARGS__)
#else
#define ASSERT(condition, format, ...)
#endif

#define FATAL(condition, format, ...) Debugger::get().fatal((condition), __FILE__, __LINE__, format, ##__VA_ARGS__)
#define EXIT(format, ...) Debugger::get().fatal(false, __FILE__, __LINE__, format, ##__VA_ARGS__)