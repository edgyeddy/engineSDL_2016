#pragma once
namespace vortex {
	
	class GameMain {
	protected:
		static GameMain *sInstance; //!< Single static instance of the game engine.
	protected:
		GameMain();
	public:
		static GameMain *getInstance(); //!< Return the single instance of the game (engine) main.
	};
}
