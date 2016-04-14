#pragma once
#include "baseWidget.h"
#include "textLabelWidget.h"
#include <string>
#include "SDL.h"
namespace vortex {
	//! UI widget: A clickable button.
	class ClickableButtonWidget : public TextLabelWidget {
	public:
		std::string mNormalBackgroundPath; //!< Path to normal background texture.
		std::string mPressedBackgroundPath; //!< Path to pressed background texture.
		SDL_Surface *mNormalBackgroundSurface; //!< Normal background surface.
		SDL_Surface *mPressedBackgroundSurface; //!< Pressed background surface.
	protected:
		bool mIsPressed = false; //!< Mouse cursor was above the button when a l-click down event was produced.
		bool mIsHover = false; //!< Mouse cursor is above the button.
	public:
		//! Setter
		inline void setPressed(bool value) {
			mIsPressed = value;
		}
		//! Getter
		inline bool isPressed() {
			return mIsPressed;
		}
		//! Setter
		inline void setHover(bool value) {
			mIsHover = value;
		}
		//! Getter
		inline bool isHover() {
			return mIsHover;
		}
	protected:
		//! Getter
		virtual SDL_Surface *getCurrentBackgroundTexture() {
			if (isPressed()) { 
			//if (isPressed() || isHover()) {
				return mPressedBackgroundSurface;
			}
			else {
				return mNormalBackgroundSurface;
			}
		}
		//! Must be implemented in derived class
		virtual void _initialize() override;
		//! Must be implemented in derived class
		virtual void _dispose() override;
	public:
		//! Constructor
		ClickableButtonWidget(const std::string &text,
			const std::string &normalBackgroundTexture,
			const std::string &pressedBackgroundTexture,
			const Color4 &textColor, 
			const Rectangle &virtualRectangle) : TextLabelWidget(text, textColor, Color4::getColor4(), virtualRectangle) {
			mNormalBackgroundPath= normalBackgroundTexture;
			mPressedBackgroundPath = pressedBackgroundTexture;
		}
	protected:
		virtual void draw(SDL_Window *window) override; //!< Inform the scene that the window must be redrawn; must be re-implemented in derived class.
		virtual void resize(SDL_Window *windowOldSize, int width, int height) override;
	public:
		//! Event handler.
		virtual bool onMouseMovementEvent(SDL_MouseMotionEvent event) override;
		//! Event handler.
		virtual bool onMouseClickDownEvent(SDL_MouseButtonEvent event);
		//! Event handler.
		virtual bool onMouseClickUpEvent(SDL_MouseButtonEvent event);
	protected:
		//! Event handler.
		virtual void onMouseClickUpEvent() { }
	};
}