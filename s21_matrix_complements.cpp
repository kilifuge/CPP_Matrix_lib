#include "s21_matrix_oop.h"

S21Matrix S21Matrix::CalcMinor(size_t expRow, size_t expColumn) const {
  S21Matrix minor(rows - 1, columns - 1);
  size_t minor_row = 0;
  for (size_t i = 0; i < rows; i++) {
    if (i != expRow - 1) {
      size_t minor_col = 0;
      for (size_t j = 0; j < columns; j++) {
        if (j != expColumn - 1) {
          minor.matrix[minor_row][minor_col] = matrix[i][j];
          minor_col++;
        }
      }
      minor_row++;
    }
  }
  return minor;
}

double S21Matrix::FindAlgebraicDop(size_t expRow, size_t expColumn) const {
  S21Matrix minor = CalcMinor(expRow, expColumn);
  double res = minor.Determinant();
  res *= pow(-1, (double)expRow + (double)expColumn);
  if (fabs(res) < EPS) res = 0.0;
  return res;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows != columns)
    throw std::runtime_error("Матрица не является квадратной.");

  S21Matrix result(rows, columns);
  if (rows == 1) {
    result.matrix[0][0] = 1.0;
    return result;
  }
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < columns; j++) {
      double alg = FindAlgebraicDop(i + 1, j + 1);
      result.matrix[i][j] = alg;
    }
  }
  return result;
}