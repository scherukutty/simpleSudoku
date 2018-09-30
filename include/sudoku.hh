#ifndef SUDOKU_HH
#define SUDOKU_HH
#include <array>
#include <iostream>
#include <set>
#define MATRIX_SIZE 9
#define SECTION_SIZE 3
using std ::array, std::set;

class Sudoku {
private:
  array<array<short, MATRIX_SIZE>, MATRIX_SIZE> matrix;
  array<array<set<short>, MATRIX_SIZE>, MATRIX_SIZE> possibilities;

public:
  // IO
  void printSet(set<short> inputSet);
  void printMatrix();
  void printPossibilities();
  void fetchMatrix();

  // Processing
  set<short> fetchHorizontal(short row);
  set<short> fetchVertical(short column);
  set<short> fetchSection(short row, short column);
  set<short> getDiff(set<short> set1, set<short> set2);
  set<short> getProbables(short row, short column);
  set<short> narrowProbables(short row, short column);
  void loadPossibilities();
  bool updatePossibilities();
  bool isSolved();
  bool solve();
};
#endif // !SUDOKU_HH