#pragma once
#include "SDL.h"
#include "UserEventData.h"
namespace vortex {
	class IEventListener {
		public:
			//! Event handler.
			virtual bool onUserEvent(UserEventData *data) = 0;
			//! Event handler.
			virtual bool onMouseMovementEvent(SDL_MouseMotionEvent event) = 0;
			//! Event handler.
			virtual bool onMouseClickDownEvent(SDL_MouseButtonEvent event) = 0;
			//! Event handler.
			virtual bool onMouseClickUpEvent(SDL_MouseButtonEvent event) = 0;
			//! Event handler.
			virtual bool onKeyPressedEvent(int keyId) = 0;
	};
}
