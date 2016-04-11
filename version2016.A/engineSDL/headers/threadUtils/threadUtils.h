#include <chrono>
#include <thread>

namespace vortex {
	/// Contains thread-related utility functions
	class ThreadUtils {
	public:
		//! Sleeps (blocking) this thread for the specified number of seconds.
		static void sleepThisThreadSeconds(int numSeconds) {
			std::this_thread::sleep_for(std::chrono::seconds(3));
		}
	};
}