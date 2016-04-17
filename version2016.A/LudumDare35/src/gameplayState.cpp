#include "gameplayState.h"
#include "Rectangle.h"
#include "mySceneManager.h"
#include "Utils.h"
#include <sstream>
namespace vortex {
	int GameplayState::NUM_SYMBOLS = 6;
	int GameplayState::NUM_COLUMNS = 10;
	int GameplayState::NUM_ROWS = 6;
	int GameplayState::DEBUG_STARTING_LEVEL = 0;
	void GameplayState::tryShapeshift() {
		int nn = getCurrentFragment().size();
		int firstVal = getCurrentFragment()[0];
		// before: A - B - C - D - E
		// after:  B - C - D - E - A
		for (int ii = 1; ii < nn; ii++) {
			getCurrentFragment()[ii - 1] = getCurrentFragment()[ii];
		}
		getCurrentFragment()[nn - 1] = firstVal;
	}
	bool GameplayState::isCurrentFloatingFragmentInsideGrid() {
		// Position last + 1 MUST BE != -1 or out-of-array
		int col = mFloatingCellColumnIndexGlobal - OFFSET_ROW_FIXED_TO_GLOBAL;
		int row = mFloatingCellRowIndexGlobal - OFFSET_ROW_FIXED_TO_GLOBAL;
		int nextRow = row + getCurrentFragment().size();
		if (nextRow < NUM_ROWS && mFixedPiecesCurrent->getValueAt(col, nextRow) == -1) {
			return false;
		}
		if (col >= 0 && col < NUM_COLUMNS && row >= 0 && row < NUM_ROWS) {
			return true;
		}
		else {
			return false;
		}
	}
	void GameplayState::copyCurrentFragmentToCurrentArray() {
		for (int jj = 0; jj < (int)getCurrentFragment().size(); jj++) {
			int val = getCurrentFragment()[jj];
			int col = mFloatingCellColumnIndexGlobal - OFFSET_ROW_FIXED_TO_GLOBAL;
			int row = mFloatingCellRowIndexGlobal - OFFSET_ROW_FIXED_TO_GLOBAL + jj;
			mFixedPiecesCurrent->setValueAt(val, col, row);
		}
	}
	bool GameplayState::checkVictory(void) {
		bool victory = true;
		int nCol = mFixedPiecesCurrent->getNumColumns();
		int nRow = mFixedPiecesCurrent->getNumRows();
		for (int ii = 0; ii < nCol && victory; ii++) {
			for (int jj = 0; jj < nRow && victory; jj++) {
				int val1 = mFixedPiecesCurrent->getValueAt(ii, jj);
				if (val1 < 0) {
					int locMinX = mFloatingCellColumnIndexGlobal - OFFSET_COLUMN_FIXED_TO_GLOBAL;
					int locMinY = mFloatingCellRowIndexGlobal - OFFSET_ROW_FIXED_TO_GLOBAL;
					int locMaxX = locMinX + 0;
					int locMaxY = locMinY + getCurrentFragment().size() - 1;
					if (ii >= locMinX && ii <= locMaxX && jj >= locMinY && jj <= locMaxY) {
						// Replace current space with the value from the floating piece
						val1 = getCurrentFragment()[jj - locMinY];
					}
				}
				int val2 = mFixedPiecesSolution->getValueAt(ii, jj);
				if (val2 != -1 && val1 != val2) {
					std::ostringstream oss;
					oss << "Failure i=" << ii << " j=" << jj << " valCurrent=" << val1 << " valSolution=" << val2;
					Logger::d(oss.str());
					victory = false;
				}
			}
		}
		if (victory) {
			Logger::t("Victory!");
		}
		return victory;
	}
	void GameplayState::loadDataFromJson(Json::Value root, Array<int> *array2D, std::string name) {
		Json::Value default;
		Json::Value itemFixed = root.get(name, default);
		for (unsigned ii = 0; ii < itemFixed.size(); ii++) {
			Json::Value entry0 = itemFixed[ii];
			Json::Value itemColumn = entry0.get("col", default);
			int columnFixed = itemColumn.asInt();
			Json::Value itemSymbols = entry0.get("symbols", default);
			for (unsigned jj = 0; jj < itemSymbols.size(); jj++) {
				Json::Value entry1 = itemSymbols[jj];
				int index = entry1.asInt();
				array2D->setValueAt(index, columnFixed, NUM_ROWS - 1 - jj);
			}
		}
	}

	void GameplayState::_initialize() {
		// TODO
		mFixedPiecesSolution = new Array<int>(NUM_COLUMNS, NUM_ROWS);
		mFixedPiecesCurrent = new Array<int>(NUM_COLUMNS, NUM_ROWS);
		// Preload all symbols
		for (int ii = 0; ii < NUM_SYMBOLS; ii++) {
			std::ostringstream oss;
			oss << "resources/symbol" << ii << ".bmp";
			SDL_Surface *preload = SDL_LoadBMP(oss.str().c_str());
			mOriginalTextureNames.push_back(oss.str());
			mOriginalTextures.push_back(preload);
			mScaledTextures.push_back(nullptr);
		}
		mFloatingFragmentIndex = 0;
		mFloatingFragments.clear();

		// Initialize values at random
		int nCol = mFixedPiecesCurrent->getNumColumns();
		int nRow = mFixedPiecesCurrent->getNumRows();
		for (int ii = 0; ii < nCol; ii++) {
			int test0 = rand() % nCol;
			for (int jj = nRow - 1; jj >= 0; jj--) {
				mFixedPiecesCurrent->setValueAt(-1, ii, jj);
				mFixedPiecesSolution->setValueAt(-1, ii, jj);
				/*
				if (jj < test0) {
					mFixedPieces->setValueAt(-1, ii, jj);
				}
				else {
					int val = (rand() % (NUM_SYMBOLS));
					mFixedPieces->setValueAt(val, ii, jj);
				}
				*/
			}
		}
		std::string jsonFile = GameplayState::getJsonFileForLevel(mLevel);
		Json::Value root = SDLUtils::loadJson(jsonFile);
		Json::Value default;
		// Initialize floating column
		{
			Json::Value itemFloat = root.get("float", default);
			for (unsigned ii = 0; ii < itemFloat.size(); ii++) {
				mFloatingFragments.push_back(std::vector<int>());
				Json::Value entry0 = itemFloat[ii];
				Json::Value itemSymbols = entry0.get("symbols", default);
				unsigned nn = itemSymbols.size();
				for (unsigned jj = 0; jj < nn; jj++) {
					Json::Value entry1 = itemSymbols[nn - 1 - jj];
					int index = entry1.asInt();
					mFloatingFragments[ii].push_back(index);
				}
			}
		}
		// Initialize pieces
		{
			this->loadDataFromJson(root, mFixedPiecesCurrent, "fixed");
			this->loadDataFromJson(root, mFixedPiecesSolution, "solution");
		}

		// Initialize floating column
		mFloatingCellColumnIndexGlobal = INITIAL_FLOATING_COLUMN_INDEX_GLOBAL;
		mFloatingCellRowIndexGlobal = INITIAL_FLOATING_ROW_INDEX_GLOBAL;
	}
	void GameplayState::_dispose() {
		// TODO
		delete mFixedPiecesCurrent;
		mFixedPiecesCurrent = nullptr;

		delete mFixedPiecesSolution;
		mFixedPiecesSolution = nullptr;

		mOriginalTextureNames.clear();
		mOriginalTextures.clear(); // Not owned
		mScaledTextures.clear(); // Not owned
	}
	void GameplayState::resize(SDL_Window *windowOldSize, int width, int height) {
		// TODO
		// Compute real dock position
		Rectangle screenRect(width, height);

		Rectangle vrect = Rectangle::getVirtualWorld();
		Rectangle srect = vrect.createInsideWithRatio(screenRect, vrect.Rect.w, vrect.Rect.h);

		mRealCellSize = srect.Rect.h / 12;
		mRealCellOffsetX = srect.Rect.x;
		mRealCellOffsetY = srect.Rect.y;

		// Scale all surfaces to new sizes
		for (int ii = 0; ii < NUM_SYMBOLS; ii++) {
			SDL_Surface *originalImage = mOriginalTextures[ii];
			SDL_Surface *scaledImage = mScaledTextures[ii];
			scaledImage = SDLUtils::scaleSurfaceIfNeeded(originalImage, scaledImage, mRealCellSize, mRealCellSize, "Symbol.Scaled");
			mScaledTextures[ii] = scaledImage;
		}
	}
	Rectangle GameplayState::getRealPositionForCellGlobal(int col, int row) {
		Rectangle out = Rectangle(mRealCellSize, mRealCellSize, mRealCellOffsetX + mRealCellSize*(col), mRealCellOffsetY + mRealCellSize*(row));
		return out;
	}
	Rectangle GameplayState::getRealPositionForCellFixed(int col, int row) {
		return getRealPositionForCellGlobal(col + OFFSET_COLUMN_FIXED_TO_GLOBAL, row + OFFSET_ROW_FIXED_TO_GLOBAL);
	}
	void GameplayState::draw(SDL_Window *window) {
		// TODO
		// For every position, draw a scaled surface there
		int nCol = mFixedPiecesCurrent->getNumColumns();
		int nRow = mFixedPiecesCurrent->getNumRows();
		for (int ii = 0; ii < nCol; ii++) {
			for (int jj = 0; jj < nRow; jj++) {
				Rectangle realCell = getRealPositionForCellFixed(ii, jj);
				int value = mFixedPiecesCurrent->getValueAt(ii, jj);
				if (value >= 0) {
					SDLUtils::renderSurfaceToWindow(window, mScaledTextures[value], realCell);
				}
			}
		}
		// Draw floating vector
		for (int ii = 0, nn = getCurrentFragment().size(); ii < nn; ii++) {
			Rectangle realCell = getRealPositionForCellGlobal(mFloatingCellColumnIndexGlobal, mFloatingCellRowIndexGlobal + ii);
			SDLUtils::renderSurfaceToWindow(window, mScaledTextures[getCurrentFragment()[ii]], realCell);
		}
	}
	void GameplayState::update(SDL_Window *window, int deltaMs) {
		// TODO
	}
	bool GameplayState::onUserEvent(UserEventData *data) {
		// TODO
		return false;
	}
	bool GameplayState::onMouseMovementEvent(SDL_MouseMotionEvent event) {
		// TODO
		return false;
	}
	bool GameplayState::onMouseClickDownEvent(SDL_MouseButtonEvent event) {
		// TODO
		return false;
	}
	bool GameplayState::onMouseClickUpEvent(SDL_MouseButtonEvent event) {
		// TODO
		return false;
	}
	int GameplayState::getFirstOccupiedRowForColumnFixed(int col) {
		int numRow = mFixedPiecesCurrent->getNumRows();
		for (int jj = 0; jj < numRow; jj++) {
			if (mFixedPiecesCurrent->getValueAt(col, jj) >= 0) {
				return jj;
			}
		}
		return numRow;
	}
	bool GameplayState::canMoveFloatingToGlobal(int deltaX, int deltaY) {
		int newCol = mFloatingCellColumnIndexGlobal + deltaX;
		int newRow = mFloatingCellRowIndexGlobal + deltaY;
		if (newCol < OFFSET_COLUMN_FIXED_TO_GLOBAL) { return false; }
		if (newCol >= (OFFSET_COLUMN_FIXED_TO_GLOBAL + NUM_COLUMNS)) { return false; }
		if (newRow < 0) { return false; }
		int index = OFFSET_ROW_FIXED_TO_GLOBAL + getFirstOccupiedRowForColumnFixed(newCol - OFFSET_COLUMN_FIXED_TO_GLOBAL);
		if (newRow > (index - (int)getCurrentFragment().size())) { return false; }

		// TODO: Check every base index

		return true;
	}
	bool GameplayState::tryNextFragment(void) {
		if (mFloatingFragmentIndex >= ((int)mFloatingFragments.size() - 1)) {
			return false;
		}
		// If possible, fix the current floating fragment to current array
		if (isCurrentFloatingFragmentInsideGrid()) {
			copyCurrentFragmentToCurrentArray();
			// If possible, change current fragment index
			if (mFloatingFragmentIndex < ((int)mFloatingFragments.size() - 1)) {
				mFloatingFragmentIndex++;
				// Set fragment position to starting position
				// Initialize floating column
				mFloatingCellColumnIndexGlobal = INITIAL_FLOATING_COLUMN_INDEX_GLOBAL;
				mFloatingCellRowIndexGlobal = INITIAL_FLOATING_ROW_INDEX_GLOBAL;
				// Inform scene that the fragment has changed
				GameMain::getInstance()->launchUserEvent(MySceneManager::SceneEventsEnum::USER_EVENT_NEXT_FRAGMENT, 0, 0, false);
				return true;
			}
		}
		return false;
	}
	bool GameplayState::onKeyPressedEvent(int keyId) {
		if (keyId == SDLK_LSHIFT || keyId == SDLK_RSHIFT || keyId == SDLK_SPACE) {
			tryShapeshift();			
		}
		else if (keyId == SDLK_BACKSPACE) {
			GameMain::getInstance()->launchUserEvent(MySceneManager::SceneEventsEnum::USER_EVENT_RESTART_LEVEL, 0, 0, false);
		}
		else if (keyId == SDLK_RETURN) {
			GameMain::getInstance()->launchUserEvent(MySceneManager::SceneEventsEnum::USER_EVENT_NEXT_FRAGMENT_REQUEST, 0, 0, false);			
		}

		if (keyId == SDLK_LEFT) {
			if (canMoveFloatingToGlobal(-1, 0)) {
				mFloatingCellColumnIndexGlobal--;
			}
		}
		else if (keyId == SDLK_RIGHT) {
			if (canMoveFloatingToGlobal(+1, 0)) {
				mFloatingCellColumnIndexGlobal++;
			}
		}
		if (keyId == SDLK_UP) {
			if (canMoveFloatingToGlobal(0, -1)) {
				mFloatingCellRowIndexGlobal--;
			}
		}
		else if (keyId == SDLK_DOWN) {
			if (canMoveFloatingToGlobal(0, +1)) {
				mFloatingCellRowIndexGlobal++;
			}
		}
		if (checkVictory()) {
			// TODO: Lock UI
			GameMain::getInstance()->launchUserEvent(MySceneManager::SceneEventsEnum::USER_EVENT_SHOW_END_LEVEL_FX, 0, 0, false);
			GameMain::getInstance()->launchUserEventAfterDelay(DELAY_VICTORY_MS, MySceneManager::SceneEventsEnum::USER_EVENT_NEXT_LEVEL, 0, 0, false);
			GameMain::getInstance()->lockUI(true);
		}
		return true; // Capture all keystrokes
	}
}