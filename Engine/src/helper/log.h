#pragma once

#include "spdlog/spdlog.h"


#if defined(ENGINE_DEBUG) && defined(USER_ENGINE)
	#define ADD_FILE_LINE(x) std::string(\
											"[ " +\
											std::string(__FILE__).substr(std::string(__FILE__).find_last_of("\\") + 1) +\
											" : " +\
											std::to_string(__LINE__) + " ] " +\
											std::string(x)\
										)

	#ifdef LOG_DETAILED
		#define LOG_CRITICAL(x, ...)	prev::Logger::Log(User::ENGINE, LOG_LEVEL_CRITICAL, ADD_FILE_LINE(x) __VA_ARGS__)
		#define LOG_ERROR(x, ...)		prev::Logger::Log(User::ENGINE, LOG_LEVEL_ERROR, ADD_FILE_LINE(x)  __VA_ARGS__)
		#define LOG_WARN(x, ...)		prev::Logger::Log(User::ENGINE, LOG_LEVEL_WARN, ADD_FILE_LINE(x)  __VA_ARGS__)
		#define LOG_INFO(x, ...)		prev::Logger::Log(User::ENGINE, LOG_LEVEL_INFO, ADD_FILE_LINE(x) __VA_ARGS__)
		#define LOG_TRACE(x, ...)		prev::Logger::Log(User::ENGINE, LOG_LEVEL_TRACE, ADD_FILE_LINE(x) __VA_ARGS__)
	#else
		#define LOG_CRITICAL(x, ...)	prev::Logger::Log(User::ENGINE, LOG_LEVEL_CRITICAL, x __VA_ARGS__)
		#define LOG_ERROR(x, ...)		prev::Logger::Log(User::ENGINE, LOG_LEVEL_ERROR, x  __VA_ARGS__)
		#define LOG_WARN(x, ...)		prev::Logger::Log(User::ENGINE, LOG_LEVEL_WARN, x  __VA_ARGS__)
		#define LOG_INFO(x, ...)		prev::Logger::Log(User::ENGINE, LOG_LEVEL_INFO, x __VA_ARGS__)
		#define LOG_TRACE(x, ...)		prev::Logger::Log(User::ENGINE, LOG_LEVEL_TRACE, x __VA_ARGS__)
	#endif

#elif defined(ENGINE_DEBUG)

	#ifdef LOG_DETAILED
		#define LOG_CRITICAL(x, ...)	prev::Logger::Log(User::CLIENT, LOG_LEVEL_CRITICAL, ADD_FILE_LINE(x) __VA_ARGS__)
		#define LOG_ERROR(x, ...)		prev::Logger::Log(User::CLIENT, LOG_LEVEL_ERROR, ADD_FILE_LINE(x)  __VA_ARGS__)
		#define LOG_WARN(x, ...)		prev::Logger::Log(User::CLIENT, LOG_LEVEL_WARN, ADD_FILE_LINE(x)  __VA_ARGS__)
		#define LOG_INFO(x, ...)		prev::Logger::Log(User::CLIENT, LOG_LEVEL_INFO, ADD_FILE_LINE(x) __VA_ARGS__)
		#define LOG_TRACE(x, ...)		prev::Logger::Log(User::CLIENT, LOG_LEVEL_TRACE, ADD_FILE_LINE(x) __VA_ARGS__)
	#else
		#define LOG_CRITICAL(x, ...)	prev::Logger::Log(User::CLIENT, LOG_LEVEL_CRITICAL, x __VA_ARGS__)
		#define LOG_ERROR(x, ...)		prev::Logger::Log(User::CLIENT, LOG_LEVEL_ERROR, x  __VA_ARGS__)
		#define LOG_WARN(x, ...)		prev::Logger::Log(User::CLIENT, LOG_LEVEL_WARN, x  __VA_ARGS__)
		#define LOG_INFO(x, ...)		prev::Logger::Log(User::CLIENT, LOG_LEVEL_INFO, x __VA_ARGS__)
		#define LOG_TRACE(x, ...)		prev::Logger::Log(User::CLIENT, LOG_LEVEL_TRACE, x __VA_ARGS__)
	#endif

#endif

namespace prev {

	enum LogLevel {
		LOG_LEVEL_CRITICAL,
		LOG_LEVEL_ERROR,
		LOG_LEVEL_WARN,
		LOG_LEVEL_INFO,
		LOG_LEVEL_TRACE,
		LOG_LEVEL_UNKNOWN
	};

	enum class User {
		ENGINE,
		CLIENT
	};

	class Logger {
		using LogCallbackFunc = std::function<void(std::string, LogLevel)>;
	public:
		static void Initialize();

		template<typename ... Args>
		static void Log(User user, LogLevel level, const std::string & fmt, const Args & ... args) {

			auto logger = m_CoreLogger;

			if (user == User::CLIENT) {
				logger = m_ClinetLogger;
			}

			switch (level) {
			case LOG_LEVEL_CRITICAL:
				logger->critical(fmt, args ...);
				break;
			case LOG_LEVEL_ERROR:
				logger->error(fmt, args ...);
				break;
			case LOG_LEVEL_WARN:
				logger->warn(fmt, args ...);
				break;
			case LOG_LEVEL_INFO:
				logger->info(fmt, args ...);
				break;
			case LOG_LEVEL_TRACE:
				logger->trace(fmt, args ...);
				break;
			case LOG_LEVEL_UNKNOWN:
				logger->trace(fmt, args ...);
				break;
			default:
				break;
			}

		}

		static void AddLogCallback(LogCallbackFunc callbackFunction);
	private:
		static std::shared_ptr<spdlog::logger> m_CoreLogger;
		static std::shared_ptr<spdlog::logger> m_ClinetLogger;
	};

}