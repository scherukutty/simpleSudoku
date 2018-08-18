#include "sudoku.hh"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <unistd.h>
using std::string, std::cin, std::cout;

void printSet(set<short> inputSet) {
  for (auto i : inputSet) {
    cout << i << " ";
  }
  cout << "\n";
}

void Sudoku ::fetchMatrix() {
  int line; /* Each line is read as a integer and loaded to matrix */
  for (short i = 0; i < 9; i++) {
    cin >> line;
    line %= 1000000000;
    for (short j = 8; j >= 0; j--) {
      short value = line % 10;
      line /= 10;
      matrix[i][j] = value;
    }
  }
}

void Sudoku::printMatrix() {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      cout << matrix[i][j];
    }
    cout << "\n";
  }
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
  short sectionMinColumnOffset = (column / 3) * 3;
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

void Sudoku::printPossibilities() {
  for (short i = 0; i < 9; i++) {
    for (short j = 0; j < 9; j++) {
      if (matrix[i][j] != 0)
        continue;
      cout << "[" << i << "][" << j << "] : ";
      printSet(possibilities[i][j]);
    }
  }
}

bool Sudoku::updatePossibilities() {
  bool hasUpdate = false;
  for (short i = 0; i < MAT_SIZE; i++) {
    for (short j = 0; j < MAT_SIZE; j++) {
      if (matrix[i][j] == 0) {
        set<short> probables = getProbables(i, j);
        possibilities[i][j] = probables;
        if (probables.size() == 1) {
          for (auto selected : probables)
            matrix[i][j] = selected;
          hasUpdate = true;
        }
      }
    }
  }
  return hasUpdate;
}

set<short> Sudoku::getProbables(short row, short column) {
  set<short> section = fetchSquare(row, column);
  set<short> vertical = fetchVertical(column);
  set<short> horizontal = fetchHorizontal(row);
  set<short> possibility;
  for (short i = 1; i <= 9; i++)
    possibility.insert(i);
  set<short> temp;

  std::set_difference(possibility.begin(), possibility.end(), section.begin(),
                      section.end(), std::inserter(temp, temp.begin()));
  possibility.clear();
  possibility = temp;
  temp.clear();

  std::set_difference(possibility.begin(), possibility.end(), vertical.begin(),
                      vertical.end(), std::inserter(temp, temp.begin()));

  possibility.clear();
  possibility = temp;
  temp.clear();

  std::set_difference(possibility.begin(), possibility.end(),
                      horizontal.begin(), horizontal.end(),
                      std::inserter(temp, temp.begin()));
  possibility.clear();
  possibility = temp;
  temp.clear();
  return possibility;
}

bool Sudoku::isSolved() {
  bool isSolved = true;
  for (short i = 0; i < 9 && isSolved == true; i++) {
    for (short j = 0; j < 9 && isSolved == true; j++) {
      if (matrix[i][j] == 0)
        isSolved = false;
    }
  }
  return isSolved;
}

bool Sudoku::solve() {
  while (updatePossibilities())
    ;
  return isSolved();
}

int main() {
  Sudoku sudoku;
  sudoku.fetchMatrix();
  sudoku.printMatrix();
  if (sudoku.solve()) {
    cout << "\n\nSudoku Solved"
         << "\n\n";
    sudoku.printMatrix();
  } else {
    cout << "\n\nSudoku Simplified to"
         << "\n\n";
    sudoku.printMatrix();
    sudoku.printPossibilities();
  }
  return 0;
}
