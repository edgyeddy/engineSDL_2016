#pragma once

namespace vortex {
	/// Engine constants
	class Constants {
	public:
		static const int MINIMUM_UPDATE_INTERVAL_MS = 5; //!< Do not update more than 200 times per second.
		static const int DELAY_PRINT_FPS_MS = 5 * 1000; //!< Prints the FPS value every X ms.

		static const int WINDOWED_WINDOW_WIDTH = 640; //!< Default window width
		static const int WINDOWED_WINDOW_HEIGHT = 480; //!< Default window height
		static const bool USE_FULLSCREEN = false; //!< Default fullscreen mode
		static const int FULLSCREEN_WINDOW_WIDTH = 1024; //!< Default window width
		static const int FULLSCREEN_WINDOW_HEIGHT = 768; //!< Default window height
		static const int SCREEN_FLAGS_WINDOWED; //!< Default windowed flags
		static const int SCREEN_FLAGS_FULLSCREEN; //!< Default fullscreen flags

		// @PRODUCTION false
		static const bool DEBUG_ENABLE = true; //!< To enable debug code 
		// @PRODUCTION false
		static const bool DEBUG_VERBOSE = true; //!< To enable verbose debug code. Requires DEBUG_ENABLE set. 
	};
}
