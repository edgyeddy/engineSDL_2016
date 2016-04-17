#include "ui/textLabelWidget.h"
#include "color4.h"
#include "gameMain.h"
#include "Utils.h"

namespace vortex {
	void TextLabelWidget::_initialize() {
		if (mText.length() > 0) {
			mTextOriginal = GameMain::getInstance()->getTextManager()->renderTextToSurface(mText, mTextColor); //  , Color4::getColor4(0, 0, 0));
		}
		else {
			mTextOriginal = nullptr;
		}
	}
	void TextLabelWidget::_dispose() {
		// SDL_FreeSurface(mTextSurface); Not owned by me
		mTextSurface = nullptr;

		if (mTextOriginal) {
			SDL_FreeSurface(mTextOriginal);
			mTextOriginal = nullptr; // Owned by me
		}
	}
	void TextLabelWidget::setText(const std::string &text) {
		mText = text;
		// Dispose old original
		SDL_Surface *oldOriginalPointer = mTextOriginal;
		SDL_FreeSurface(mTextOriginal);
		mTextOriginal = nullptr; // Owned by me
		// Forget old scaled original
		if (mTextSurface != nullptr) {
			GameMain::getInstance()->getAssetsManager()->forgetBitmapReference(oldOriginalPointer, mTextSurface->w, mTextSurface->h);
		}
		// Destroy old scaled original (not owned by me)
		mTextSurface = nullptr;

		// Create new original
		if (mText.length() > 0) {
			mTextOriginal = GameMain::getInstance()->getTextManager()->renderTextToSurface(mText, mTextColor); //  , Color4::getColor4(0, 0, 0));
		}
		else {
			mTextOriginal = nullptr;
		}

		// Recompute new text screen position
		// Regenerate new scaled original (not owned by me)
		Rectangle wRect = GameMain::getInstance()->getWindowSize();
		SDL_Window *window = GameMain::getInstance()->getWindow();
		this->resize(window, wRect.Rect.w, wRect.Rect.h);
	}

	void TextLabelWidget::draw(SDL_Window *window) {
		SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
		// Draw background
		SDLUtils::renderColorRectangleToSurface(mBackgroundColor, mWidgetScreenPosition, screenSurface, true);
		// Draw text
		if (mTextSurface != nullptr) {
			SDLUtils::renderSurfaceToWindow(window, mTextSurface, mTextScreenPosition);
		}
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
		if (mTextOriginal != nullptr) {
			mTextSurface = SDLUtils::scaleSurfaceIfNeeded(mTextOriginal, mTextSurface, mTextScreenPosition.Rect.w, mTextScreenPosition.Rect.h, "TextLabel.Text.scaled");
		}
		//SDL_FreeSurface(original);
		//original = nullptr;
		// Compute text position and size
		// Regenerate texture
		//mTextSurface = SDLUtils::scaleSurfaceIfNeeded(originalImage, mBackgroundImage, newImageSize.Rect.w, newImageSize.Rect.h);
	}
}