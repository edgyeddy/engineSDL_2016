#pragma once
#include <stdint.h>

namespace vortex {
	/// Represents a user event that can be send to the game main. This event can be routed to the current scene object.
	class UserEventData {
	public:
		/*
		enum EventType {
			EVENT_GAME_ANIMATION_COMPLETED,
			EVENT_CHANGE_TO_NEXT_SCREEN,
			EVENT_GAME_CHANGED_FOCUS_LCLICK,
			EVENT_GAME_CHANGED_FOCUS_HOVER,
			EVENT_PRINT_FPS
		};
		*/
	public:
		int type; //!< Event type
		int64_t data1; //!< First event data
		int64_t data2; //!< Second event data
		bool repeat; //!< Id the event recurrent?
	};
}
