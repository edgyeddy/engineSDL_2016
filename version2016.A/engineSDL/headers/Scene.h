#pragma once
#include "ui\UiManager.h"
#include "UserEventData.h"
#include "IDisposableObject.h"
#include <SDL.h>

namespace vortex {
	/// Represents a scene (screen) of the game
	class Scene : public IDisposableObject {
	protected:
		UiManager *mUiManager; //!< UiManager for this scene.
		float mRatio = 0; //!< Debug Background color animation
		SDL_Color mBackgroundColor; //!< Background color for this scene
	protected:
		void _initialize() override;
		void _dispose() override;
	protected:
		//! Draw the scene background.
		void drawFront(SDL_Window *window, bool updateFramebuffer);
		//! Draw the scene foreground (UI).
		void drawBack(SDL_Window *window, bool updateFramebuffer);
	public:
		// Life-cycle management
		virtual void resize(SDL_Window *windowOldSize, int width, int height); //!< Inform the scene that the window has been resized; must be re-implemented in derived class.
		virtual void draw(SDL_Window *window, bool updateFramebuffer); //!< Inform the scene that the window must be redrawn; must be re-implemented in derived class.
		virtual void update(SDL_Window *window, int deltaMs); //!< Inform the scene that a time interval has passed; must be re-implemented in derived class.
	public:
		virtual bool onUserEvent(UserEventData *data) { 
			return mUiManager->onUserEvent(data);
		} //!< Inform the scene of a user event; must be re-implemented in derived class. The event is not owned by the scene.
		
		  //! Event handler.
		virtual bool onMouseMovementEvent(SDL_MouseMotionEvent event) {
			return mUiManager->onMouseMovementEvent(event);
		}
		//! Event handler.
		virtual bool onMouseClickDownEvent(SDL_MouseButtonEvent event) {
			return mUiManager->onMouseClickDownEvent(event);
		}
		//! Event handler.
		virtual bool onMouseClickUpEvent(SDL_MouseButtonEvent event) { 
			return mUiManager->onMouseClickUpEvent(event);
		}
		//! Event handler.
		virtual bool onKeyPressedEvent(int keyId) { 
			return mUiManager->onKeyPressedEvent(keyId);
		}
	};
}
