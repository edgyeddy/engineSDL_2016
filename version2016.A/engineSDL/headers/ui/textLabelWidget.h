#pragma once 
#include "baseWidget.h"
#include <string>
#include "SDL.h"
#include "color4.h"

namespace vortex {
	//! UI widget: A text label.
	class TextLabelWidget : public BaseWidget {
	protected:
		Color4 mBackgroundColor; //!< Background color
		Color4 mTextColor; //!< Text color
		std::string mText; //!< Text to display
		SDL_Surface *mTextOriginal; //!< Original surface with text.
		SDL_Surface *mTextSurface = nullptr; //!< Scaled surface with text.
		Rectangle mWidgetScreenPosition; //!< Screen position for the widget.
		Rectangle mTextScreenPosition; //!< Text screen bounding box should smaller than the widget screen bounding box
	protected:
		//! Must be implemented in derived class
		virtual void _initialize() override;
		//! Must be implemented in derived class
		virtual void _dispose() override;
	public:
		void setText(const std::string &text);
		//! Constructor
		TextLabelWidget(const std::string &text, const Color4 &textColor, const Color4 &backColor, const Rectangle &virtualRectangle) : BaseWidget(virtualRectangle) {
			mTextColor = textColor; 
			mBackgroundColor = backColor;
			mText = text;
		}
		virtual void draw(SDL_Window *window) override; //!< Inform the scene that the window must be redrawn; must be re-implemented in derived class.
		//! Apply resizing to this widget.
		virtual void resize(SDL_Window *windowOldSize, int width, int height) override;
	};
}