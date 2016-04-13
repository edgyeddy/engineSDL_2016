#pragma once
#include "SDL.h"
namespace vortex {
	//! Wraps the SDL_Rect struct.
	class Rectangle {
	public:
		//! Modes of rectangle adjustment.
		enum RectangleAdjustEnum {
			STRETCH_TO_FIT, 
			ADJUST_INSIDE,
			ADJUST_OUTSIDE
		};
	public:
		SDL_Rect Rect; //!< Public wrapped struct.
	public:
		//! Constructor
		Rectangle(int w = 0, int h = 0, int x = 0, int y = 0) {
			this->Rect.w = w;
			this->Rect.h = h;
			this->Rect.x = x;
			this->Rect.y = y;
		}
		//! Creates a rectangle of the same size of the given surface.
		static Rectangle createForSurface(SDL_Surface *surface) {
			Rectangle out = Rectangle(surface->w, surface->h, 0, 0);
			return out;
		}
		//! Creates a rectangle so the input area matches.
		static Rectangle stretchToFit(const Rectangle &targetScreenSize) {
			Rectangle out;
			out = targetScreenSize;
			return out;
		}
		//! Creates a rectangle so the input area is fully outside it.
		static Rectangle createInsideWithRatio(const Rectangle &area, int lengthX, int lengthY) {
			Rectangle out;
			double ratioSrc = (double)area.Rect.w / (double)area.Rect.h;
			double ratioDst = (double)lengthX / (double)lengthY;

			if (ratioDst < ratioSrc) {
				// Add left-right bars
				out.Rect.h = area.Rect.h;
				out.Rect.w = (int)(out.Rect.h * ratioDst);
				out.Rect.y = area.Rect.y;
				out.Rect.x = area.Rect.x + (area.Rect.w - out.Rect.w) / 2;
			}
			else {
				// Add top-down bars
				out.Rect.w = area.Rect.w;
				out.Rect.h = (int)(out.Rect.w / ratioDst);
				out.Rect.x = area.Rect.x;
				out.Rect.y = area.Rect.y + (area.Rect.h - out.Rect.h) / 2;
			}
			return out;
		}
		//! Creates a rectangle so the input area is fully inside it.
		static Rectangle createOutsideWithRatio(const Rectangle &area, int lengthX, int lengthY) {
			Rectangle out;
			double ratioSrc = (double)area.Rect.w / (double)area.Rect.h;
			double ratioDst = (double)lengthX / (double)lengthY;

			if (ratioDst < ratioSrc) {
				// Match target width, crop height
				out.Rect.w = area.Rect.w;
				out.Rect.h = (int)(out.Rect.w / ratioDst);
				out.Rect.x = area.Rect.x;
				out.Rect.y = area.Rect.y + (area.Rect.h - out.Rect.h) / 2;
			}
			else {
				// Match target height, crop width
				out.Rect.h = area.Rect.h;
				out.Rect.w = (int)(out.Rect.h * ratioDst);
				out.Rect.y = area.Rect.y;
				out.Rect.x = area.Rect.x + (area.Rect.w - out.Rect.w) / 2;

			}
			return out;
		}
		//! Adjusts source rectangle to target rectangle, according to adjustment mode.
		static Rectangle adjustRectangle(RectangleAdjustEnum mode, const Rectangle &sourceRect, const Rectangle &targetRect) {
			Rectangle newImageSize;
			if (mode == RectangleAdjustEnum::STRETCH_TO_FIT) {
				newImageSize = Rectangle::stretchToFit(targetRect);
			}
			else if (mode == RectangleAdjustEnum::ADJUST_INSIDE) {
				newImageSize = Rectangle::createInsideWithRatio(targetRect, sourceRect.Rect.w, sourceRect.Rect.h);
			}
			else if (mode == RectangleAdjustEnum::ADJUST_OUTSIDE) {
				newImageSize = Rectangle::createOutsideWithRatio(targetRect, sourceRect.Rect.w, sourceRect.Rect.h);
			}
			newImageSize.centerInParent(targetRect);
			return newImageSize;
		}
		//! Centers this rectangle inside the parent rectangle.
		void centerInParent(const Rectangle &parent) {
			// 1) Updates this->xy to center this in the parent box
			this->Rect.x = parent.Rect.x + (parent.Rect.w - this->Rect.w) / 2;
			this->Rect.y = parent.Rect.y + (parent.Rect.h - this->Rect.h) / 2;
		}
		//! To string.
		std::string toString() const {
			std::ostringstream oss;
			oss << "rect[w=" << Rect.w << " h=" << Rect.h << " x=" << Rect.x << " y=" << Rect.y << "]";
			return oss.str();
		}
		Rectangle mapVirtualToReal(int realWidth, int realHeight, int virtualWidth, int virtualHeight) const {
			Rectangle real;
			Rectangle realWindow(realWidth, realHeight, 0, 0);
			Rectangle realTarget = createInsideWithRatio(realWindow, virtualWidth, virtualHeight);
			// Map self virtual coordinates to real target coordinates
			float scaleX = (float)realTarget.Rect.w / (float)virtualWidth;
			float scaleY = (float)realTarget.Rect.h / (float)virtualHeight;
			real.Rect.w = (int)(this->Rect.w * scaleX);
			real.Rect.h = (int)(this->Rect.h * scaleY);
			real.Rect.x = realTarget.Rect.x + (int)(this->Rect.x * scaleX);
			real.Rect.y = realTarget.Rect.y + (int)(this->Rect.y * scaleY);

			return real;
		}
	};
}
