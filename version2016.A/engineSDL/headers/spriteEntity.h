#pragma once
#include "IDisposableObject.h"
#include "IDrawable.h"
#include "IEventListener.h"
namespace vortex {
	class SpriteEntity : public IDrawable, public IDisposableObject, public IEventListener {
	public:
	};
}
