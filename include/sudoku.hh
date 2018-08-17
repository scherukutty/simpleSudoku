#ifndef SUDOKU_HH
#define SUDOKU_HH
#include <array>
#include <iostream>
#include <vector>
using std::vector, std ::array;

class Sudoku {
private:
  array<array<short, 9>, 9> matrix;
  array<vector<short>, 81> possibilities;

public:
  int solve();
  int fetchMatrix();
  int printMatrix();
  int updatePossibilities();
};
#endif // !SUDOKU_HH