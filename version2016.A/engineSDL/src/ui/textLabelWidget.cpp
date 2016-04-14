#include "ui/textLabelWidget.h"
#include "color4.h"
#include "gameMain.h"
#include "Utils.h"

namespace vortex {
	void TextLabelWidget::_initialize() {
		mTextOriginal = GameMain::getInstance()->getTextManager()->renderTextToSurface(mText, mTextColor); //  , Color4::getColor4(0, 0, 0));
	}
	void TextLabelWidget::_dispose() {
		// SDL_FreeSurface(mTextSurface); Not owned by me
		mTextSurface = nullptr;

		mTextOriginal = nullptr; // Not owned by me
	}
	void TextLabelWidget::draw(SDL_Window *window) {
		SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
		// Draw background
		SDL_FillRect(screenSurface, &mWidgetScreenPosition.Rect, SDL_MapRGB(screenSurface->format, mBackgroundColor.Color.r, mBackgroundColor.Color.g, mBackgroundColor.Color.b));
		// Draw text
		SDLUtils::renderSurfaceToWindow(window, mTextSurface, mTextScreenPosition);
	}
	void TextLabelWidget::resize(SDL_Window *windowOldSize, int width, int height) {
		BaseWidget::resize(windowOldSize, width, height);

		// Recompute screen position from virtual screen position
		mWidgetScreenPosition = mVirtualRectangle.mapVirtualToReal(width, height, Constants::VIRTUAL_WIDTH, Constants::VIRTUAL_HEIGHT);
		Rectangle textBox = GameMain::getInstance()->getTextManager()->getTextBoundingBox(mText);
		/*
		// Now centers the text inside the provided position
		textBox.centerInParent(mTextScreenPosition);
		mTextScreenPosition = textBox;
		*/
		mTextScreenPosition = Rectangle::createInsideWithRatio(mWidgetScreenPosition, textBox.Rect.w, textBox.Rect.h);
		// Resize text size to target size
		//SDL_Surface *original = GameMain::getInstance()->getTextManager()->renderTextToSurface(mText, mTextColor); //  , Color4::getColor4(0, 0, 0));
		mTextSurface = SDLUtils::scaleSurfaceIfNeeded(mTextOriginal, mTextSurface, mTextScreenPosition.Rect.w, mTextScreenPosition.Rect.h, "TextLabel.Text.scaled");
		//SDL_FreeSurface(original);
		//original = nullptr;
		// Compute text position and size
		// Regenerate texture
		//mTextSurface = SDLUtils::scaleSurfaceIfNeeded(originalImage, mBackgroundImage, newImageSize.Rect.w, newImageSize.Rect.h);
	}
}