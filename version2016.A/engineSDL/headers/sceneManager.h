#pragma once
#include "IDisposableObject.h"
#include "Scene.h"

namespace vortex {
	/// Manages the current scene of the game
	class SceneManager : public IDisposableObject {
	protected:
		Scene *mCurrentScene; //!< Pointer to the owned current scene
	protected:
		void _initialize() override;
		void _dispose() override;
	public:
		/// Getter
		Scene *getCurrentScene();
		/// Checker
		bool hasScene();
		/// Loads (and gains ownership) of the given scene
		Scene *loadScene(int sceneId);
		/// Unloads the current scene
		void unloadScene();
	protected:
		virtual Scene *_loadScene(int sceneId) { return nullptr;  } //!< Created a scene of the required type, must be redefined in derived class
	};
}