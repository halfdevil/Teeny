#include "Core/Logger.h"

bool Logger::canLog(LogLevel logLevel) const
{
	return logLevel >= mMaxLogLevel;
}

void Logger::setMaxLogLevel(LogLevel logLevel)
{
	mMaxLogLevel = logLevel;
}

void Logger::write(LogLevel logLevel, const char* format, ...)
{
	constexpr uint32_t MAX_BUFFER_LEN = 4096;

	char buffer[MAX_BUFFER_LEN];
	va_list args;

	va_start(args, format);
	vsnprintf(buffer, MAX_BUFFER_LEN, format, args);
	va_end(args);

	switch (logLevel)
	{
	case LogLevel::Info:
		std::cout << "[INFO]: " << buffer << "\n";
		break;

	case LogLevel::Debug:
		std::cout << "[DEBUG]: " << buffer << "\n";
		break;

	case LogLevel::Warning:
		std::cout << "[WARNING]: " << buffer << "\n";
		break;

	case LogLevel::Error:
		std::cout << "[ERROR]: " << buffer << "\n";
		break;

	case LogLevel::Fatal:
		std::cout << "[FATAL]: " << buffer << "\n";
		break;

	default:
		break;
	}
}