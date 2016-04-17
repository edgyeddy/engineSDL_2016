#pragma once
#include "IDisposableObject.h"
#include "IDrawable.h"
#include "IEventListener.h"
#include "vortexUtils/templateArray.h"
#include <vector>
#include "Rectangle.h"
#include "json\json.h"
#include <sstream>
namespace vortex {
	class GameplayState : public IDisposableObject, IDrawable, IEventListener {
	public:
		static int NUM_SYMBOLS;
		static int NUM_COLUMNS;
		static int NUM_ROWS;
		static int DEBUG_STARTING_LEVEL;
		static const int DELAY_VICTORY_MS = 1000;
		static const int OFFSET_COLUMN_FIXED_TO_GLOBAL = 6;
		static const int OFFSET_ROW_FIXED_TO_GLOBAL = 6;
		static const int INITIAL_FLOATING_ROW_INDEX_GLOBAL = 0;
		static const int INITIAL_FLOATING_COLUMN_INDEX_GLOBAL = OFFSET_COLUMN_FIXED_TO_GLOBAL + (10) / 2;

	protected:
		int mLevel;
		int mFloatingCellColumnIndexGlobal;
		int mFloatingCellRowIndexGlobal;
		int mFloatingFragmentIndex = 0;
		std::vector<std::vector<int> > mFloatingFragments;
		Array<int> *mFixedPiecesCurrent;
		Array<int> *mFixedPiecesSolution;
		std::vector<std::string>mOriginalTextureNames;
		std::vector<SDL_Surface *>mOriginalTextures;
		std::vector<SDL_Surface *>mScaledTextures;
		int mRealCellSize = 0;
		int mRealCellOffsetX = 0;
		int mRealCellOffsetY = 0;
	public:
		void tryShapeshift(void);
		bool tryNextFragment(void);
		inline std::vector<int> &getCurrentFragment() {
			return mFloatingFragments[mFloatingFragmentIndex];
		}
		inline int getNumPendingFragments() {
			return mFloatingFragments.size() - mFloatingFragmentIndex;
		}
		static inline std::string getJsonFileForLevel(int level) {
			std::ostringstream oss;
			oss << "resources/level" << level << ".json";
			return oss.str();
		}
	protected:
		bool isCurrentFloatingFragmentInsideGrid(void);
		void copyCurrentFragmentToCurrentArray(void);
		bool checkVictory(void);
		void loadDataFromJson(Json::Value root, Array<int> *array2D, std::string name);
		int getFirstOccupiedRowForColumnFixed(int col);
		bool canMoveFloatingToGlobal(int deltaX, int deltaY);
		Rectangle getRealPositionForCellGlobal(int col, int row);
		Rectangle getRealPositionForCellFixed(int col, int row);
	protected:
		virtual void _initialize() override;
		virtual void _dispose() override;
	public:
		GameplayState(int level) {
			mLevel = level;
		}
	public:
		virtual void resize(SDL_Window *windowOldSize, int width, int height) override;
		virtual void draw(SDL_Window *window) override;
		virtual void update(SDL_Window *window, int deltaMs) override;
	public:
		virtual bool onUserEvent(UserEventData *data) override;
		virtual bool onMouseMovementEvent(SDL_MouseMotionEvent event) override;
		virtual bool onMouseClickDownEvent(SDL_MouseButtonEvent event) override;
		virtual bool onMouseClickUpEvent(SDL_MouseButtonEvent event) override;
		virtual bool onKeyPressedEvent(int keyId) override;
	};
}
