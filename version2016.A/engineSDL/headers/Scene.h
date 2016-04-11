#pragma once
#include "UserEventData.h"
#include "IDisposableObject.h"
#include <SDL.h>

namespace vortex {
	/// Represents a scene (screen) of the game
	class Scene : public IDisposableObject {
	protected:
		float mRatio = 0; //!< Debug Background color animation
		SDL_Color mBackgroundColor; //!< Background color for this scene
	protected:
		void _initialize() override;
		void _dispose() override;
	public:
		// Life-cycle management

		virtual void resize(SDL_Window *window, int width, int height); //!< Inform the scene that the window has been resized; must be re-implemented in derived class.
		virtual void draw(SDL_Window *window, bool updateFramebuffer); //!< Inform the scene that the window must be redrawn; must be re-implemented in derived class.
		virtual void update(SDL_Window *window, int deltaMs); //!< Inform the scene that a time interval has passed; must be re-implemented in derived class.
	public:
		// Event handlers
		void onUserEvent(UserEventData *data); //!< Inform the scene of a user event; must be re-implemented in derived class. The event is not owned by the scene.
	};
}
