#pragma once
#include "IDisposableObject.h"
#include "SDL.h"
#include "baseWidget.h"
#include "UserEventData.h"

namespace vortex {
	//! A class to manage all UI widgets.
	class UiManager : public IDisposableObject {
	protected:
		BaseWidget *mRoot; //!< Root widget.
	protected:
		//! Must be implemented in derived class
		virtual void _initialize() override;
		//! Must be implemented in derived class
		virtual void _dispose() override;
	public:
		/// Gains ownership. Must be initialized before setting it.
		void setRootWidget(BaseWidget *rootWidget) {
			if (mRoot != nullptr) {
				throw Exception(TR("Root widget already exists!"));
			}
			if (!rootWidget->isInitialized()) {
				throw NotInitializedException();
			}
			mRoot = rootWidget;
		}
		virtual void resize(SDL_Window *windowOldSize, int width, int height); //!< Inform the scene that the window has been resized; must be re-implemented in derived class.
		virtual void draw(SDL_Window *window); //!< Inform the scene that the window must be redrawn; must be re-implemented in derived class.
		virtual void update(SDL_Window *window, int deltaMs); //!< Inform the scene that a time interval has passed; must be re-implemented in derived class.
	public:
		//! Event handler.
		bool onUserEvent(UserEventData *data);
		//! Event handler.
		bool onMouseMovementEvent(SDL_MouseMotionEvent event);
		//! Event handler.
		bool onMouseClickDownEvent(SDL_MouseButtonEvent event);
		//! Event handler.
		bool onMouseClickUpEvent(SDL_MouseButtonEvent event);
		//! Event handler.
		bool onKeyPressedEvent(int keyId);
	};
}
