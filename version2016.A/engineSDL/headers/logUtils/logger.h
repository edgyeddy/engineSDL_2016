#include <string>
#include <exception>
#include "vortexUtils\exception.h"

namespace vortex {
	class Logger {
	public:
		//! Prints a debug text to std::cout
		static void d(std::string msg);
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