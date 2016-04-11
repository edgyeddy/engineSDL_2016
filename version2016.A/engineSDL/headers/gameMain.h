#pragma once
namespace vortex {
	
	class GameMain {
	protected:
		static GameMain *sInstance;
	protected:
		GameMain();
	public:
		static GameMain *getInstance();
	};
}
