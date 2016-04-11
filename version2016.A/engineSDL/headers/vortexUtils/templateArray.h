#pragma once
namespace vortex {
	template <class T>

	//! Templated 2D array in column-order
	class Array {
	protected:
		int numRows; //!< Number of rows
		int numColumns; //!< Number of columns
		T **arrayPerColumns; //!< 2D array
	public:
		/// Getter
		inline int getNumColumns() {
			return numColumns;
		}
		/// Getter
		inline int getNumRows() {
			return numRows;
		}
		/// Constructor
		Array<T>::Array(int nColumns, int nRows) {
			numColumns = nColumns;
			numRows = nRows;
			// Create array
			arrayPerColumns = new T*[nColumns];
			for (int ii = 0; ii < numColumns; ii++) {
				arrayPerColumns[ii] = new T[nRows];
				for (int jj = 0; jj < numRows; jj++) {
					//arrayPerColumns[ii][jj] = nullptr;
				}
			}
		}
		/// Destructor
		Array<T>::~Array() {
			for (int ii = 0; ii < numColumns; ii++) {
				delete arrayPerColumns[ii];
				for (int jj = 0; jj < numRows; jj++) {
					// Contents must be deleted before destroying this.
					//delete arrayPerColumns[ii][jj];
					//arrayPerColumns[ii][jj] = nullptr;
				}
			}
			delete arrayPerColumns;
			arrayPerColumns = nullptr;
		}
		/// Setter
		void Array<T>::setValueAt(T value, int column, int row) {
			arrayPerColumns[column][row] = value;
		}
		/// Getter
		T Array<T>::getValueAt(int column, int row) {
			return arrayPerColumns[column][row];
		}
		/// Switch the values of 2 cells
		void Array<T>::switchValues(int column1, int row1, int column2, int row2) {
			T temp = arrayPerColumns[column1][row1];
			arrayPerColumns[column1][row1] = arrayPerColumns[column2][row2];
			arrayPerColumns[column2][row2] = temp;
		}
		/// Returns the cell index of the first matching object, or false if not found.
		bool Array<T>::findFirstMatchIndex(T reference, int *column, int *row) {
			for (int ii = 0; ii < numColumns; ii++) {
				for (int jj = 0; jj < numRows; jj++) {
					if (arrayPerColumns[ii][jj] == reference) {
						*column = ii;
						*row = jj;
						return true;
					}
				}
			}
			*column = -1;
			*row = -1;
			return false;
		}
	};
}
