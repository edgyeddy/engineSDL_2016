#pragma once
#include "ui\UiManager.h"
#include "UserEventData.h"
#include "IDisposableObject.h"
#include <SDL.h>

namespace vortex {
	/// Represents a scene (screen) of the game
	class Scene : public IDisposableObject {
	protected:
		UiManager *mUiManager;
		float mRatio = 0; //!< Debug Background color animation
		SDL_Color mBackgroundColor; //!< Background color for this scene
	protected:
		void _initialize() override;
		void _dispose() override;
	protected:
		void drawFront(SDL_Window *window, bool updateFramebuffer);
		void drawBack(SDL_Window *window, bool updateFramebuffer);
	public:
		// Life-cycle management

		virtual void resize(SDL_Window *windowOldSize, int width, int height); //!< Inform the scene that the window has been resized; must be re-implemented in derived class.
		virtual void draw(SDL_Window *window, bool updateFramebuffer); //!< Inform the scene that the window must be redrawn; must be re-implemented in derived class.
		virtual void update(SDL_Window *window, int deltaMs); //!< Inform the scene that a time interval has passed; must be re-implemented in derived class.
	public:
		// Event handlers
		virtual bool onUserEvent(UserEventData *data) { 
			return mUiManager->onUserEvent(data);
		} //!< Inform the scene of a user event; must be re-implemented in derived class. The event is not owned by the scene.
		virtual bool onMouseMovementEvent(SDL_MouseMotionEvent event) {
			return mUiManager->onMouseMovementEvent(event);
		}
		virtual bool onMouseClickDownEvent(SDL_MouseButtonEvent event) {
			return mUiManager->onMouseClickDownEvent(event);
		}
		virtual bool onMouseClickUpEvent(SDL_MouseButtonEvent event) { 
			return mUiManager->onMouseClickUpEvent(event);
		}
		virtual bool onKeyPressedEvent(int keyId) { 
			return mUiManager->onKeyPressedEvent(keyId);
		}
	};
}
