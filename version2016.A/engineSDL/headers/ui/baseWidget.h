#pragma once
#include "IDisposableObject.h"
#include "SDL.h"
#include "Rectangle.h"
#include "UserEventData.h"

namespace vortex {
	//! UI widget: A generic widget.
	class BaseWidget : public IDisposableObject {
	public:
		BaseWidget *parentWidget = nullptr; //!< Reference to parent widget, or null.
	protected:
		Rectangle mScreenRectangle; //!< Screen position and size for this widget.
		Rectangle mVirtualRectangle; //!< Virtual position and size for this widget.
	public:
		//! Getter
		Rectangle getVirtualRectangle() const {
			return mVirtualRectangle;
		}
		//! Setter
		void setVirtualRectangle(const Rectangle &virtualRectangle) {
			mVirtualRectangle = virtualRectangle;
		}
	protected:
		//! Must be implemented in derived class
		virtual void _initialize() override;
		//! Must be implemented in derived class
		virtual void _dispose() override;
	public:
		//! Compute widget screen coordinates from widget's virtual coordinates.
		void computeRealCoordinates(int realOffsetX, int realOffsetY);
		//! Compute widget screen coordinates from widget's virtual coordinates.
		void computeRealCoordinates(int screenWidth, int screenHeight, int realOffsetX, int realOffsetY) {
			// Maps virtual rectangle to screen rectangle
			mScreenRectangle = mVirtualRectangle.mapVirtualToReal(screenWidth, screenHeight, Constants::VIRTUAL_WIDTH, Constants::VIRTUAL_HEIGHT);
			/*
			mScreenRectangle.Rect.x += realOffsetX;
			mScreenRectangle.Rect.y += realOffsetY;
			*/
		}
	public:
		//! Event handler.
		virtual bool onUserEvent(UserEventData *data);
		//! Event handler.
		virtual bool onMouseMovementEvent(SDL_MouseMotionEvent event);
		//! Event handler.
		virtual bool onMouseClickDownEvent(SDL_MouseButtonEvent event);
		//! Event handler.
		virtual bool onMouseClickUpEvent(SDL_MouseButtonEvent event);
		//! Event handler.
		virtual bool onKeyPressedEvent(int keyId);
	public:
		//! Constructor
		BaseWidget(const Rectangle &virtualRectangle) {
			mVirtualRectangle = virtualRectangle;
		}
		//! Apply resizing to this widget.
		virtual void resize(SDL_Window *windowOldSize, int width, int height) {
			this->computeRealCoordinates(width, height, 0, 0);

		} //!< Inform the scene that the window has been resized; must be re-implemented in derived class.
		virtual void draw(SDL_Window *window) = 0; //!< Inform the scene that the window must be redrawn; must be re-implemented in derived class.
		//! Inform the scene that a time interval has passed; must be re-implemented in derived class.
		virtual void update(SDL_Window *window, int deltaMs) { }; 
	};
}