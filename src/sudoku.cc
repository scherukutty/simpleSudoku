#include "sudoku.hh"
#include <algorithm>
#include <iostream>
#include <iterator>

using std::string, std::cin, std::cout;

void Sudoku::printSet(set<short> inputSet) {
  for (auto i : inputSet) {
    cout << i << " ";
  }
  cout << "\n";
}

void Sudoku::printMatrix() {
  for (int i = 0; i < MATRIX_SIZE; i++) {
    for (int j = 0; j < MATRIX_SIZE; j++) {
      cout << matrix[i][j];
    }
    cout << "\n";
  }
}

void Sudoku::printPossibilities() {
  for (short i = 0; i < MATRIX_SIZE; i++) {
    for (short j = 0; j < MATRIX_SIZE; j++) {
      if (matrix[i][j] != 0)
        continue;
      cout << "[" << i << "][" << j << "] : ";
      printSet(possibilities[i][j]);
    }
  }
}

void Sudoku ::fetchMatrix() {
  int line; /* Each line is read as a integer and loaded to matrix */
  for (short i = 0; i < MATRIX_SIZE; i++) {
    cin >> line;
    line %= 1000000000;
    for (short j = 8; j >= 0; j--) {
      short value = line % 10;
      line /= 10;
      matrix[i][j] = value;
    }
  }
}

set<short> Sudoku::fetchHorizontal(short row) {
  set<short> returnSet;
  for (short column = 0; column < MATRIX_SIZE; column++) {
    short value = matrix[row][column];
    if (value != 0) {
      returnSet.insert(value);
    }
  }
  return returnSet;
}

set<short> Sudoku::fetchVertical(short column) {
  set<short> returnSet;
  for (short row = 0; row < MATRIX_SIZE; row++) {
    short value = matrix[row][column];
    if (value != 0) {
      returnSet.insert(value);
    }
  }
  return returnSet;
}

set<short> Sudoku::fetchSection(short row, short column) {
  set<short> returnSet;
  short sectionMinRowOffset = (row / SECTION_SIZE) * SECTION_SIZE;
  short sectionMinColumnOffset = (column / SECTION_SIZE) * SECTION_SIZE;
  short sectionMaxRowOffset = sectionMinRowOffset + SECTION_SIZE;
  short sectionMaxColumnOffset = sectionMinColumnOffset + SECTION_SIZE;

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

set<short> Sudoku::getDiff(set<short> set1, set<short> set2) {
  set<short> temp;
  std::set_difference(set1.begin(), set1.end(), set2.begin(), set2.end(),
                      std::inserter(temp, temp.begin()));
  return temp;
}

set<short> Sudoku::getProbables(short row, short column) {

  set<short> section = fetchSection(row, column);
  set<short> vertical = fetchVertical(column);
  set<short> horizontal = fetchHorizontal(row);
  set<short> possibility = possibilities[row][column];

  for (short i = 1; i <= MATRIX_SIZE; i++)
    possibility.insert(i);

  possibility = getDiff(possibility, section);
  possibility = getDiff(possibility, vertical);
  possibility = getDiff(possibility, horizontal);
  return possibility;
}

set<short> Sudoku::narrowProbables(short row, short column) {
  set<short> probables = getProbables(row, column);
  possibilities[row][column] = probables;
  bool pickPossibleElseWhere;
  for (auto pick : probables) {
    pickPossibleElseWhere = false;
    short sectionMinRowOffset = (row / SECTION_SIZE) * SECTION_SIZE;
    short sectionMinColumnOffset = (column / SECTION_SIZE) * SECTION_SIZE;
    short sectionMaxRowOffset = sectionMinRowOffset + SECTION_SIZE;
    short sectionMaxColumnOffset = sectionMinColumnOffset + SECTION_SIZE;

    for (short sectionRow = sectionMinRowOffset;
         sectionRow < sectionMaxRowOffset; sectionRow++) {
      for (short sectionColumn = sectionMinColumnOffset;
           sectionColumn < sectionMaxColumnOffset; sectionColumn++) {

        if (!(row == sectionRow && column == sectionColumn) &&
            matrix[sectionRow][sectionColumn] == 0) {
          set<short> temp = getProbables(sectionRow, sectionColumn);
          possibilities[sectionRow][sectionColumn] = temp;
          if (temp.count(pick) > 0) {
            pickPossibleElseWhere = true;
          }
        }
      }
    }
    if (!pickPossibleElseWhere) {
      set<short> selected = {pick};
      return selected;
    }
  }
  return probables;
}

void Sudoku::loadPossibilities() {
  set<short> probables;
  for (short i = 0; i < MATRIX_SIZE; i++) {
    for (short j = 0; j < MATRIX_SIZE; j++) {
      if (matrix[i][j] == 0) {
        probables = getProbables(i, j);
        possibilities[i][j] = probables;
        if (probables.size() == 1) {
          for (auto selected : probables)
            matrix[i][j] = selected;
        }
      }
    }
  }
}

bool Sudoku::updatePossibilities() {
  bool hasUpdate = false;
  set<short> probables;

  for (short i = 0; i < MATRIX_SIZE; i++) {
    for (short j = 0; j < MATRIX_SIZE; j++) {
      if (matrix[i][j] == 0) {
        probables = narrowProbables(i, j);
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

bool Sudoku::isSolved() {
  bool isSolved = true;
  for (short i = 0; i < MATRIX_SIZE && isSolved == true; i++) {
    for (short j = 0; j < MATRIX_SIZE && isSolved == true; j++) {
      if (matrix[i][j] == 0)
        isSolved = false;
    }
  }
  return isSolved;
}

bool Sudoku::solve() {
  loadPossibilities();
  while (updatePossibilities())
    ;
  return isSolved();
}

int main() {
  Sudoku sudoku;
  sudoku.fetchMatrix();
  sudoku.printMatrix();

  if (sudoku.solve()) {
    cout << "\nSudoku Solved!!"
         << "\n\n";
    sudoku.printMatrix();
  } else {
    cout << "\nSudoku Simplified to:"
         << "\n\n";
    sudoku.printMatrix();
    sudoku.printPossibilities();
  }
  return 0;
}
