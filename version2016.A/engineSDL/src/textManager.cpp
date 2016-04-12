#pragma once
#include "SDL_ttf.h"
#include "textManager.h"
#include "constants.h"
namespace vortex {
	void TextManager::_initialize() {
		int errcode = TTF_Init();
		if (errcode != 0) {
			Logger::e(TR("Error initializing TTF."));
			return;
		}
		// Default font
		mFont = TTF_OpenFont(Constants::DEFAULT_FONT_PATH, Constants::DEFAULT_FONT_SIZE);
		// Default colors
		mForegroundColor = Color4::getColor4(255, 255, 255);
		mBackgroundColor = Color4::getColor4(0, 0, 0, 0);
	}
	void TextManager::_dispose() {
		TTF_CloseFont(mFont);
		TTF_Quit();
	}
	TextManager::TextManager() {
		// NOOP
	}
	SDL_Surface *TextManager::renderTextToSurface(const char *text, const Color4 &foregroundColor, const Color4 &backgroundColor) {
		SDL_Surface* textSurface = TTF_RenderText_Shaded(mFont, text, foregroundColor.Color, backgroundColor.Color);
		//SDL_Surface* textSurface = TTF_RenderText_Blended(mFont, text, foregroundColor.Color);
		return textSurface;
	}
	SDL_Surface *TextManager::renderTextToSurface(const char *text, const Color4 &foregroundColor) {
		//SDL_Surface* textSurface = TTF_RenderText_Shaded(mFont, text.c_str(), foregroundColor.Color, backgroundColor.Color);
		SDL_Surface* textSurface = TTF_RenderText_Blended(mFont, text, foregroundColor.Color);
		return textSurface;
	}
	SDL_Surface *TextManager::renderTextToSurface(std::string &text, const Color4 &foregroundColor, const Color4 &backgroundColor) {
		return renderTextToSurface(text.c_str(), foregroundColor, backgroundColor);
	}
	SDL_Surface *TextManager::renderTextToSurface(std::string &text, const Color4 &foregroundColor) {
		return renderTextToSurface(text.c_str(), foregroundColor);
	}
	Rectangle TextManager::getTextBoundingBox(std::string &text) {
		return getTextBoundingBox(text.c_str());
	}
	Rectangle TextManager::getTextBoundingBox(const char *text) {
		Rectangle rect;
		TTF_SizeText(mFont, text, &(rect.Rect.w), &(rect.Rect.h));
		return rect;
	}
}