#include <chrono>
#include <thread>

namespace vortex {
	class ThreadUtils {
	public:
		//! Sleeps (blocking) this thread for the specified number of seconds.
		static void SleepThisThreadSeconds(int numSeconds) {
			std::this_thread::sleep_for(std::chrono::seconds(3));
		}
	};
}