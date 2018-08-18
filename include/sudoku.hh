#ifndef SUDOKU_HH
#define SUDOKU_HH
#include <array>
#include <iostream>
#include <set>
#define MAT_SIZE 9
#define TOTAL_ENTRIES (MAT_SIZE * MAT_SIZE)
using std ::array, std::set;

class Sudoku {
private:
  array<array<short, MAT_SIZE>, MAT_SIZE> matrix;
  array<array<set<short>, MAT_SIZE>, MAT_SIZE> possibilities;

public:
  void fetchMatrix();
  void printMatrix();
  void printPossibilities();
  set<short> fetchHorizontal(short row);
  set<short> fetchVertical(short column);
  set<short> fetchSquare(short row, short column);
  set<short> getProbables(short row, short column);
  bool updatePossibilities();
  bool isSolved();
  bool solve();
};
#endif // !SUDOKU_HH