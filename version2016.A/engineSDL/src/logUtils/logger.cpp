#include "logUtils/logger.h"
#include "Windows.h"
#include "vortexUtils/exception.h"
#include <exception>
#include <sstream>
#include <iostream>
#include "constants.h"

namespace vortex {
	void Logger::d(std::string msg) {
		if (Constants::DEBUG_ENABLE) {
			Logger::log(msg, "d");
		}
	}
	void Logger::t(std::string msg) {
		Logger::log(msg, "t");
	}
	void Logger::e(std::exception &ex) {
		Logger::log("std::EXCEPTION: " + std::string(ex.what()), "e");
	}
	void Logger::e(Exception &ex) {
		Logger::log("vortex::EXCEPTION: " + ex.getText(), "e");
	}
	void Logger::e(std::string msg) {
		Logger::log("ERROR: " + msg, "e");
	}
	void Logger::w(std::string msg) {
		Logger::log("WARNING: " + msg, "w");
	}
	void Logger::log(std::string msg, std::string type) {
		std::ostringstream oss;
		oss << "[LOG/" << type << "] " << msg << std::endl;
		std::cout << oss.str();
		// Output to VisualStudio debug window
		OutputDebugStringA(oss.str().c_str());
	}
}