#pragma once

#include <string>
#include <exception>
#include "vortexUtils\exception.h"

// GNU
#ifdef __GNUG__
#define LOG_FUNC() { Logger::d(__FUNCTION__); } //!< Prints the pretty function signature.
#else
// WINDOWS
#define LOG_FUNC() { Logger::d(__FUNCSIG__); } //!< Prints the pretty function signature.
#endif

namespace vortex {
	/// Logs messages to std::cout
	class Logger {
	public:
		//! Prints a text to std::cout
		static void t(std::string msg);
		//! Prints a debug text to std::cout
		static void d(std::string msg);
		//! Prints a warning text to std::cout
		static void w(std::string msg);
		//! Prints an exception as error to std::cout
		static void e(std::exception &ex);
		//! Prints an exception as error to std::cout
		static void e(Exception &ex);
		//! Prints an error text to std::cout
		static void e(std::string msg);
	protected:
		//! Prints a labelled string to std::cout
		static void log(std::string msg, std::string type);
	};
}