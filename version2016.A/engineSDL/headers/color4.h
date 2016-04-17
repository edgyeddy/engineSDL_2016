#pragma once
#include "SDL.h"
namespace vortex {
	//! Wraps the SDL_Color struct.
	class Color4 {
	public:
		SDL_Color Color; //!< Public wrapped struct.
	public:
		inline int32_t toInt32() const {
			return (Color.r << 24 | Color.g << 16 | Color.b << 8 | Color.a);
		}
		//! Returns a Color4 from the given colors;
		static Color4 getColor4(Uint8 r = 0xFF, Uint8 g = 0x00, Uint8 b = 0x00, Uint8 a = 0xFF) {
			Color4 col;

			col.Color.r = r;
			col.Color.g = g;
			col.Color.b = b;
			col.Color.a = a;

			return col;
		}
	};
}
