#pragma once
#include <exception>
#include <string>
#include "localeUtils\translate.h"

namespace vortex {
	class Exception : public std::exception {
	protected:
		std::string mText; //!< Brief text describing this exception.
	public:
		/// Constructor
		Exception(const char *msg) {
			mText = msg;
		}
		Exception(std::string &msg) {
			mText = msg;
		}
		/// Getter
		std::string &getText() {
			return mText;
		}
	};
	class NotImplementedException : public Exception {
	public:
		NotImplementedException() : Exception(TR("This function has not been implemented yet")) {
			// NOOP
		}
	};
}
