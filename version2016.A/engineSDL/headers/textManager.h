#pragma once
#include "IDisposableObject.h"
#include "SDL_ttf.h"
#include "Rectangle.h"
#include "color4.h"

namespace vortex {
	//! Manages the text rendering.
	class TextManager : public IDisposableObject {
	protected:
		Color4 mBackgroundColor; //!< Default text background color
		Color4 mForegroundColor; //!< Default text foreground color
		TTF_Font*mFont1; //!< Default font
		TTF_Font*mFont2; //!< Large font
	protected:
		void _initialize();
		void _dispose();
	public:
		//! Getter
		inline const Color4 &getDefaultBackgroundColor() const {
			return mBackgroundColor;
		}
		//! Getter
		inline const Color4 &getDefaultForegroundColor() const {
			return mForegroundColor;
		}
		/// Constructor
		TextManager();
		
		SDL_Surface *renderTextToSurface(std::string &text, const Color4 &foregroundColor, bool useDefaultFont = true);
		//!< Renders the text to a bitmap surface. Callee is the owner of the surface.
		SDL_Surface *renderTextToSurface(std::string &text, const Color4 &foregroundColor, const Color4 &backgroundColor, bool useDefaultFont = true);
		//!< Renders the text to a bitmap surface. Callee is the owner of the surface.
		SDL_Surface *renderTextToSurface(const char *text, const Color4 &foregroundColor, bool useDefaultFont = true);
		//!< Renders the text to a bitmap surface. Callee is the owner of the surface.
		SDL_Surface *renderTextToSurface(const char *text, const Color4 &foregroundColor, const Color4 &backgroundColor, bool useDefaultFont = true);
		//!< Renders the text to a bitmap surface. Callee is the owner of the surface.
		Rectangle getTextBoundingBox(std::string &text, bool useDefaultFont = true);
		//!< Gets the bounding box for the given text.
		Rectangle getTextBoundingBox(const char *text, bool useDefaultFont = true);
		//!< Gets the bounding box for the given text.
	};
}

