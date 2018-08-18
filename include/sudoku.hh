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
  array<set<short>, TOTAL_ENTRIES> possibilities;

public:
  int solve();
  int fetchMatrix();
  int printMatrix();
  set<short> fetchHorizontal(short row);
  set<short> fetchVertical(short column);
  set<short> fetchSquare(short row, short column);
  int updatePossibilities();
};
#endif // !SUDOKU_HH