#pragma once
#include <stdint.h>

namespace vortex {
	//! A poor man simulation of delegate functions.
	class IDefaultDelegate {
	public:
		//! Callback, must be re-defined in derived class.
		virtual void run(int64_t param1, int64_t param2) = 0;
	};
}
