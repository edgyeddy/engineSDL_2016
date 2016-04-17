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
		mFont1 = TTF_OpenFont(Constants::DEFAULT_FONT_PATH, Constants::DEFAULT_FONT_SIZE);
		mFont2 = TTF_OpenFont(Constants::DEFAULT_FONT_PATH, Constants::LARGE_FONT_SIZE);
		// Default colors
		mForegroundColor = Color4::getColor4(255, 255, 255);
		mBackgroundColor = Color4::getColor4(0, 0, 0, 0);
	}
	void TextManager::_dispose() {
		TTF_CloseFont(mFont1);
		TTF_CloseFont(mFont2);
		TTF_Quit();
	}
	TextManager::TextManager() {
		// NOOP
	}
	SDL_Surface *TextManager::renderTextToSurface(const char *text, const Color4 &foregroundColor, const Color4 &backgroundColor, bool useDefaultFont) {
		SDL_Surface* textSurface = TTF_RenderText_Shaded(useDefaultFont?mFont1:mFont2, text, foregroundColor.Color, backgroundColor.Color);
		//SDL_Surface* textSurface = TTF_RenderText_Blended(mFont, text, foregroundColor.Color);
		return textSurface;
	}
	SDL_Surface *TextManager::renderTextToSurface(const char *text, const Color4 &foregroundColor, bool useDefaultFont) {
		//SDL_Surface* textSurface = TTF_RenderText_Shaded(mFont, text.c_str(), foregroundColor.Color, backgroundColor.Color);
		SDL_Surface* textSurface = TTF_RenderText_Blended(useDefaultFont ? mFont1 : mFont2, text, foregroundColor.Color);
		return textSurface;
	}
	SDL_Surface *TextManager::renderTextToSurface(std::string &text, const Color4 &foregroundColor, const Color4 &backgroundColor, bool useDefaultFont) {
		return renderTextToSurface(text.c_str(), foregroundColor, backgroundColor, useDefaultFont);
	}
	SDL_Surface *TextManager::renderTextToSurface(std::string &text, const Color4 &foregroundColor, bool useDefaultFont) {
		return renderTextToSurface(text.c_str(), foregroundColor, useDefaultFont);
	}
	Rectangle TextManager::getTextBoundingBox(std::string &text, bool useDefaultFont) {
		return getTextBoundingBox(text.c_str(), useDefaultFont);
	}
	Rectangle TextManager::getTextBoundingBox(const char *text, bool useDefaultFont) {
		Rectangle rect;
		TTF_SizeText(useDefaultFont ? mFont1 : mFont2, text, &(rect.Rect.w), &(rect.Rect.h));
		return rect;
	}
}