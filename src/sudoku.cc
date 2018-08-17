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
    for (int j = 0; j < 9; j++) {
      cout << matrix[i][j] << " ";
    }
    cout << "\n";
  }
  return 0;
}
int main() {
  Sudoku sudoku;
  sudoku.fetchMatrix();
  sudoku.printMatrix();
  return 0;
}
