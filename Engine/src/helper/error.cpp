#include "pch.h"
#include "error.h"

#include "log.h"

#define CONVERT_TO_STRING(x) #x

namespace prev {

	std::vector<Error::ErrorDispatcher::ErrorFunc> Error::ErrorDispatcher::m_DispatchFunctions;

	Error::Error(const ErrorType & errorType, const std::string & message) {
		m_ErrorLevel = errorType;
		m_Message = message;
		ErrorDispatcher::Dispatch(this);
	}

	Error::Error(const ErrorType & errorType, const std::string & message, const std::string & file, const std::string & line) {
		m_ErrorLevel = errorType;
		m_Message = message;
		m_File = file.substr(file.find_last_of("\\") + 1);
		m_Line = line;
		ErrorDispatcher::Dispatch(this);
	}

	Error::~Error() {
	}

	void Error::AddErrorFunction(std::function<void(const Error &)> func) {
		if (func) {
			ErrorDispatcher::m_DispatchFunctions.push_back(func);
		}
	}

	void Error::LogError() {
		Logger::Log(User::ENGINE, LOG_LEVEL_ERROR, "------------------------------------------");
		if (m_File.length() != 0) {
			Logger::Log(User::ENGINE, LOG_LEVEL_ERROR, ("FILE NAME  : " + m_File).c_str());
		}
		if (m_Line.length() != 0) { 
			Logger::Log(User::ENGINE, LOG_LEVEL_ERROR, ("LINE NUM   : " + m_Line).c_str());
		}
		Logger::Log(User::ENGINE, LOG_LEVEL_ERROR, ("ERROR CODE : " + m_ErrorCode).c_str());
		Logger::Log(User::ENGINE, LOG_LEVEL_ERROR, ("ERROR TYPE : " + m_ErrorType).c_str());
		Logger::Log(User::ENGINE, LOG_LEVEL_ERROR, ("ERROR DESC : " + m_Message).c_str());
		Logger::Log(User::ENGINE, LOG_LEVEL_ERROR, "------------------------------------------");
	}

	void Error::ErrorDispatcher::Dispatch(Error * error) {
		switch (error->m_ErrorLevel) {
		case ERR_TYPE_INVALID_FUNCTION:
			error->m_ErrorType = "Invalid function pointer passed";
			error->m_ErrorCode = CONVERT_TO_STRING(ERR_TYPE_INVALID_FUNCTION);
			break;
		case ERR_TYPE_UNKNOWN:
			error->m_ErrorType = "An unknown error has occurred";
			error->m_ErrorCode = CONVERT_TO_STRING(ERR_TYPE_UNKNOWN);
			break;
		default:
			break;
		}

		error->LogError();
	}

}