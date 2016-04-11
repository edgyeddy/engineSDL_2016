#include "logUtils/logger.h"
#include "Windows.h"
#include "vortexUtils/exception.h"
#include <exception>
#include <sstream>
#include <iostream>

namespace vortex {
	void Logger::d(std::string msg) {
		Logger::log(msg, "d");
	}
	void Logger::e(std::exception &ex) {
		Logger::e("std::EXCEPTION: " + std::string(ex.what()));
	}
	void Logger::e(Exception &ex) {
		Logger::e("vortex::EXCEPTION: " + ex.getText());
	}
	void Logger::e(std::string msg) {
		Logger::log(msg, "e");
	}
	void Logger::log(std::string msg, std::string type) {
		std::ostringstream oss;
		oss << "[LOG/" << type << "] " << msg << std::endl;
		std::cout << oss.str();
		// Output to VisualStudio debug window
		OutputDebugStringA(oss.str().c_str());
	}
}