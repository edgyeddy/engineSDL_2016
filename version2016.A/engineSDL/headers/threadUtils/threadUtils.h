#include <chrono>
#include <thread>

namespace vortex {
	class ThreadUtils {
	public:
		static void SleepThisThreadSeconds(int numSeconds) {
			std::this_thread::sleep_for(std::chrono::seconds(3));
		}
	};
}