#pragma once
#include <exception>
#include <string>
#include "localeUtils\translate.h"

namespace vortex {
	/// Generic exception
	class Exception : public std::exception {
	protected:
		std::string mText; //!< Brief text describing this exception.
	public:
		/// Constructor
		Exception(const char *msg) {
			mText = msg;
		}
		/// Constructor
		Exception(std::string &msg) {
			mText = msg;
		}
		/// Getter
		std::string &getText() {
			return mText;
		}
	};
	/// Pre-defined exception
	class NotImplementedException : public Exception {
	public:
		NotImplementedException() : Exception(TR("This function has not been implemented yet.")) {
			// NOOP
		}
	};
	/// Pre-defined exception
	class NotInitializedException : public Exception {
	public:
		NotInitializedException() : Exception(TR("This object has not been initialized yet.")) { }
	};
	/// Pre-defined exception
	class AlreadyInitializedException : public Exception {
	public:
		AlreadyInitializedException() : Exception(TR("This object has already been initialized.")) { }
	};
	/// Pre-defined exception
	class DeletedButStillInitializedException : public Exception {
	public:
		DeletedButStillInitializedException() : Exception(TR("This object is being deleted but has not been disposed yet.")) { }
	};

	
}
