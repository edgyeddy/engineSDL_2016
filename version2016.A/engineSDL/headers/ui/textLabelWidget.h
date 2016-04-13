#pragma once 
#include "baseWidget.h"
#include <string>
#include "SDL.h"
#include "color4.h"

namespace vortex {
	class TextLabelWidget : public BaseWidget {
	protected:
		Color4 mBackgroundColor;
		Color4 mTextColor;
		std::string mText;
		SDL_Surface *mTextSurface; //!< Owned by this class
		Rectangle mWidgetScreenPosition;
		Rectangle mTextScreenPosition; //!< Text screen bounding box should smaller than the widget screen bounding box
	protected:
		//! Must be implemented in derived class
		virtual void _initialize() override;
		//! Must be implemented in derived class
		virtual void _dispose() override;
	public:
		//! Constructor
		TextLabelWidget(const std::string &text, const Color4 &textColor, const Color4 &backColor, const Rectangle &virtualRectangle) : BaseWidget(virtualRectangle) {
			mTextColor = textColor; 
			mBackgroundColor = backColor;
			mText = text;
		}
		virtual void draw(SDL_Window *window) override; //!< Inform the scene that the window must be redrawn; must be re-implemented in derived class.
		virtual void resize(SDL_Window *windowOldSize, int width, int height) override;
	};
}