#include "sudoku.hh"
#include <iostream>
using std::string, std::cin, std::cout;

int Sudoku ::fetchMatrix() {
  int line; /* Each line is read as a integer and loaded to matrix */
  for (int i = 0; i < 9; i++) {
    cin >> line;
    line %= 1000000000;
    for (int j = 8; j >= 0; j--) {
      short value = line % 10;
      line /= 10;
      matrix[i][j] = value;
    }
  }
  return 0;
}

int Sudoku::printMatrix() {
  for (int i = 0; i < 9; i++) {
    cout << "\n-------------------\n|";
    for (int j = 0; j < 9; j++) {
      cout << matrix[i][j] << "|";
    }
  }
  cout << "\n-------------------\n";
  return 0;
}

int Sudoku::updatePossibilities() {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
    }
  }
  return 0;
}

set<short> Sudoku::fetchHorizontal(short row) {
  set<short> returnSet;
  for (short column = 0; column < MAT_SIZE; column++) {
    short value = matrix[row][column];
    if (value != 0) {
      returnSet.insert(value);
    }
  }
  return returnSet;
}

set<short> Sudoku::fetchVertical(short column) {
  set<short> returnSet;
  for (short row = 0; row < MAT_SIZE; row++) {
    short value = matrix[row][column];
    if (value != 0) {
      returnSet.insert(value);
    }
  }
  return returnSet;
}

set<short> Sudoku::fetchSquare(short row, short column) {
  set<short> returnSet;
  short sectionMinRowOffset = (row / 3) * 3;
  short sectionMinColumnOffset = (row / 3) * 3;
  short sectionMaxRowOffset = sectionMinRowOffset + 3;
  short sectionMaxColumnOffset = sectionMinColumnOffset + 3;

  for (short sectionRow = sectionMinRowOffset; sectionRow < sectionMaxRowOffset;
       sectionRow++) {
    for (short sectionColumn = sectionMinColumnOffset;
         sectionColumn < sectionMaxColumnOffset; sectionColumn++) {
      short value = matrix[sectionRow][sectionColumn];
      if (value != 0) {
        returnSet.insert(value);
      }
    }
  }
  return returnSet;
}

void printSet(set<short> inputSet) {
  for (auto i : inputSet) {
    cout << i << " ";
  }
}

int main() {
  Sudoku sudoku;
  sudoku.fetchMatrix();
  sudoku.printMatrix();
  cout << "\n";
  printSet(sudoku.fetchHorizontal(2));
  cout << "\n";
  printSet(sudoku.fetchVertical(5));
  cout << "\n";
  printSet(sudoku.fetchSquare(5, 5));
  cout << "\n";
  return 0;
}
