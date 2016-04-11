#include <string>
#include <exception>
#include "vortexUtils\exception.h"

namespace vortex {
	class Logger {
	public:
		static void d(std::string msg);
		static void e(std::exception &ex);
		static void e(Exception &ex);
		static void e(std::string msg);
		static void log(std::string msg, std::string type);
	};
}